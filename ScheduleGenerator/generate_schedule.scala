import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter}

object ScheduleGenerator{
  var level : Int = 0;

  def main(args: Array[String]): Unit = {
    val configName : String = "configuration.xml";

    try{
      var lines = this.xmlLinesToList(configName);
      val generatedString = generate(lines);
      println(generatedString);
      val writer = new PrintWriter(new File("../src/kernel/config.cpp" ));
      writer.write(generatedString);
      writer.close();
    } catch {
      case err : NoClassDefFoundError => {
        println("Class Not Found Exception");
      }
      case err : FileNotFoundException => {
        println("Input file not found");
      }
    }
  }

  // Responsible of emitting the string, such that indentation is correct
  def emit(snippet : String, level : Int = 0) : String = {
    // Increment or decrement based on the level - before emitting
    this.level += level;

    // Create indent spacing
    var indentString = "  " * this.level;
    
    // Return the string with indentation
    return indentString + snippet;
  }

  // Iterate through all nodes - depth first
  def generate (lines: Seq[Node]): String = lines match {
    case x::xs if x.child == Nil => generate(xs)
    case x::xs => this.handleNodeLabels(x) + generate(xs)
    case _ => ""
  }

  // Handle the node labels, such that code are generated based on the labels of each node (The XML tag)
  def handleNodeLabels(node : Node) : String = node.head.label match {
    // Initial setup
    case "MODULE" => {
      val includes : String = this.emitIncludes(List(
        "../types/arinc_module.h",
        "../types/channel.h", 
        "../types/error_id_action.h",
        "../types/error_id_level.h",
        "../types/general_types.h",
        "../types/memory_requirements.h",
        "../types/module_hm_table.h",
        "../types/partition.h",
        "../types/partition_hm_table.h",
        "../types/partition_memory.h",
        "../types/port_mapping.h",
        "../types/port_type.h",
        "../types/process.h",
        "../types/queuing_port.h",
        "../types/sampling_port.h",
        "../types/schedule.h",
        "../types/system_hm_table.h",
        "../types/system_state_entry.h"
      ));
      
      var emitString : String = includes + this.emit("ArincModule arincModule {\n");
      
      this.level += 1;
      emitString = emitString +
        this.emitNodeAttributeOptional(node, List(("Name", this.s), ("ModuleVersion", this.k), ("moduleId", this.k)), true);

      return emitString +
        this.generate(node.child) +
        this.emit("}\n", -1);
    }
    // Partition Specifics here - Get the number of subpartitions for allocating the size of the array
    case "Partitions" => {
      var emitString : String = this.emit("{ // Partitions\n");
      this.level += 1;
      
      return emitString +
        this.generate(node.child) +
        this.emit("}\n", -1);
    }
    // Generation for partitions and scoping rules.
    case "Partition" => {
      var partitionString = "";
      for(region <- node.child) {
        var head = region.head;

        if(this.checkAttributeValidity("Identifier", region)){
          partitionString = partitionString + 
            this.emit("{ // Partition\n") +
            this.emitNodeAttributesRequired(head, List(("Identifier", this.k), ("Affinity", this.k)), true) +
            this.emitNodeAttributeOptional(head, List(("Name", this.s)));
        }else if(this.checkAttributeValidity("Period", region)){
          partitionString = partitionString +
            this.emitNodeAttributesRequiredNum(head, List("Duration", "Period"));
        }
      }

      return partitionString + this.generate(node.child) + this.emit("},\n", -1);
    }
    // Parse memory region attributes
    case "MemoryRegions" => {
      // Loop through all MemoryRegion Tags
      val regions = node.child.filter(child => this.checkAttributeValidity("Type", child));
      var emitString : String = this.emit(f"{ // MemoryRegion\n");
      this.level += 1;

      return emitString +
        this.generateMemoryRegion(regions) +
        this.emit("}\n", -1);
    }

    case "PartitionPorts" => {
      var emitString : String = "";
      // Find all partition ports
      var partitionPorts : Seq[Node] = node.child.filter(child => child.head.label == "PartitionPort");

      // Find all queuingPort and samplingPort tags - put each in their own list
      var queuingPorts : Seq[Node] = Seq();
      var samplingPorts : Seq[Node] = Seq();
      for(child <- partitionPorts) {
        // Filter all queing ports
        queuingPorts = child.child.filter(child => this.checkAttributeValidity("MaxNbMessage", child.head)) ++ queuingPorts;
        
        // Filter all sampling ports
        samplingPorts = child.child.filter(child => this.checkAttributeValidity("MaxNbMessage", child.head) == false && this.checkAttributeValidity("MaxMessageSize", child.head)) ++ samplingPorts;
      }

      // Emit queuing ports
      var queuingString : String = "";
      if(queuingPorts.size > 0){
        emitString = emitString + this.emit(f"{ // Queuing\n");
        this.level += 1;

        emitString = emitString +
          this.generatePartitionPorts(queuingPorts, true) +
          this.emit("}\n", -1);
      }
      
      // Emit sampling ports
      var samplingString : String = "";
      if(samplingPorts.size > 0){
        emitString = emitString + this.emit(f"{ // Sampling\n");
        this.level += 1;

        emitString = emitString +
          this.generatePartitionPorts(samplingPorts, false) +
          this.emit("}\n", -1);
      }

      // Append end tag 
      return emitString;
    }
    // Partition end *** 
    // Schedules begin ***
    case "Schedules" => {
      // Retrieve all Time Windows
      var partitionTimeWindows = node.child.filter(child => this.checkAttributeValidity("PeriodicProcessingStart", child));
      val partitionNum = partitionTimeWindows.size;

      // Emit initial Schedules code
      var emitString : String = this.emit(f"{ // Schedules\n");
      this.level += 1;

      emitString = emitString + this.emit(f"{ // PartitionTimeWindows\n");
      this.level += 1;
      // Emit all the partitionWindows
      emitString = emitString + 
        this.generatePartitionSchedules(partitionTimeWindows) +
        this.emit("}\n", -1);

      return emitString + this.emit("}\n", -1);
    }

    // Schedules end ******
    case "HealthMonitoring" => {
      // Initial code gen
      var emitString : String = this.emit("HealthMonitor health_monitor {\n", 1);

      // Generate for all SystemErrors
      emitString = emitString + this.generate(node.child);

      // Handle generation for moduleHM, partitionHM and multiPartitionHm, since need of context ->
      var moduleHms = node.child.filter(child => child.head.label == "ModuleHM");
      emitString = emitString +
        this.emit(f"ModuleHM module_hm[${moduleHms.size}] {\n");
      this.level += 1;
      emitString = emitString +
        this.generateModuleHM(moduleHms) +
        this.emit(f"}\n", -1);
        
      var multiPartitions = node.child.filter(child => child.head.label == "MultiPartitionHM");
      emitString = emitString + 
        this.emit(f"MultiPartition multi_part[${multiPartitions.size}] {\n");
      this.level += 1;
      emitString = emitString +
        this.generateMultipartitions(multiPartitions) +
        this.emit("}\n", -1);

      var partitionsHM = node.child.filter(child => child.head.label == "PartitionHM");
      emitString = emitString +
        this.emit(f"PartitionHM partitions[${partitionsHM.size}] {\n");
        this.level += 1;
        emitString = emitString + 
          this.generatePartitionsHM(partitionsHM) +
          this.emit("}\n", -1);

      return emitString + this.emit("}\n", -1);
    }

    case "SystemErrors" => {
      // Generate code for systemErrors w/ scoping and indentation
      val errors = node.child.filter(child => this.checkAttributeValidity("ErrorIdentifier", child));
      var emitString = this.emit(f"SystemError system_errors[${errors.size}] {\n");
      this.level += 1;

      emitString = emitString + 
      this.generateSystemErrors(errors) +
      this.emit("}\n", -1);

      return emitString;
    }

    case _ => ""
  }

  def generatePartitionsHM(nodes : Seq[Node]) : String = nodes match {
    case x::xs if xs != Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString = this.emit("{\n");

      emitString = emitString +
        this.emitNodeAttributes(x, List("TableName", "MultiPartitionHMTableNameRef"), true) +
        this.emit(f"SystemError system_errors[${errorActions.size}] {\n");

      this.level += 1;
      emitString = emitString +
        this.generateErrorActions(errorActions, isPHM = true) +
        this.emit("}\n", -1);
      
      return emitString + this.emit("}\n", -1) + this.generatePartitionsHM(xs);
    }
    case x::xs if xs == Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString = this.emit("{\n");

      emitString = emitString +
        this.emitNodeAttributes(x, List("TableName", "MultiPartitionHMTableNameRef"), true) +
        this.emit(f"SystemError system_errors[${errorActions.size}] {\n");

      this.level += 1;
      emitString = emitString +
        this.generateErrorActions(errorActions, isPHM = true) +
        this.emit("}\n", -1);
      
      return emitString + this.emit("}\n", -1);
    }
  }

  def generateMultipartitions(nodes : Seq[Node]) : String = nodes match {
    case x::xs if xs != Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString : String = this.emit("{\n");
      
      this.level += 1;
      emitString = emitString +
        this.emitNodeAttributes(x, List("TableName"), true) +
        this.emit(f"SystemError system_errors[${errorActions.size}] {\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, isMP = true) + 
        this.emit("}\n", -1);
      
      return emitString + this.emit("},\n", -1) + this.generateMultipartitions(xs);
    }
    case x::xs if xs == Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString : String = this.emit("{\n");
      
      this.level += 1;
      emitString = emitString +
        this.emitNodeAttributes(x, List("TableName"), true) +
        this.emit(f"SystemError system_errors[${errorActions.size}] {\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, isMP = true) + 
        this.emit("}\n", -1);
      
      return emitString + this.emit("}\n", -1);
    }
  }

  def generateModuleHM(nodes : Seq[Node]) : String = nodes match {
    // If there are more nodes in the sequence
    case x::xs if xs != Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));

      var emitString : String = this.emit("{\n") +
        this.emitNodeAttributes(x, List("StateIdentifier", "Description"), true) +
        this.emit(f"ErrorAction error_actions[${errorActions.size}]{\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, true) +
        this.emit("}\n", -1);

      return emitString + this.emit("}\n", -1) + this.generateModuleHM(xs);
    }
    // If this is the last node in the sequence
    case x::xs if xs == Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));

      var emitString : String = this.emit("{\n") +
        this.emitNodeAttributes(x, List("StateIdentifier", "Description"), true) +
        this.emit(f"ErrorAction error_actions[${errorActions.size}]{\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, true) +
        this.emit("}\n", -1);

      return emitString + this.emit("}\n", -1);
    }
  }

  def generateErrorActions(nodes : Seq[Node], isHM : Boolean = false, isMP : Boolean = false, isPHM : Boolean = false) : String = nodes match {
    case x::xs if xs != Nil && isPHM => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "PartitionRecoveryAction", "ErrorLevel"), true) +
      this.emit("},\n", -1) +
      this.generateErrorActions(xs, isPHM = true);
    }
    case x::xs if xs == Nil && isPHM => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "PartitionRecoveryAction", "ErrorLevel"), true) +
      this.emit("}\n", -1);
    }
    // If there are more nodes in the sequence
    case x::xs if xs != Nil && isHM=> {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "ModuleRecoveryAction"), true) +
      this.emit("},\n", -1) +
      this.generateErrorActions(xs, true);
    }
    // If this is the last node in the sequence
    case x::xs if xs == Nil && isHM => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "ModuleRecoveryAction"), true) +
      this.emit("}\n", -1);
    }
    case x::xs if xs != Nil && isMP => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "ErrorLevel"), true) +
      this.emit("},\n", -1) +
      this.generateErrorActions(xs, isMP = true);
    }
    case x::xs if xs == Nil && isMP => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("ErrorIdentifierRef", "ErrorLevel"), true) +
      this.emit("}\n", -1);
    }
  }

  def generateSystemErrors(nodes : Seq[Node]) : String = nodes match {
    // If we have more nodes in the sequence
    case x::xs if xs != Nil => {
      return this.emit("{\n") +
        this.emitNodeAttributes(x, List("ErrorIdentifier", "Description"), true) +
        this.emit("},\n", -1) +
        this.generateSystemErrors(xs);
    }
    // If we are at the very last element
    case x::xs if xs == Nil => {
      return this.emit("{\n") +
        this.emitNodeAttributes(x, List("ErrorIdentifier", "Description"), true) +
        this.emit("}\n", -1);
    }
  }
  
  def generatePartitionSchedules(nodes : Seq[Node]) : String = nodes match {
    // If we have more elements in the list
    case x::xs if xs != Nil => 
      this.emit("{\n") +
      this.emitNodeAttributesRequired(x, List(("PeriodicProcessingStart", this.k), ("Duration", this.k), ("PartitionNameRef", this.s), ("Offset", this.k)), true) +
      this.emit("},\n", -1) +
      this.generatePartitionSchedules(xs);
    
    // If we are at the last element in the list
    case x::xs if xs == Nil => 
      this.emit("{\n") +
      this.emitNodeAttributesRequired(x, List(("PeriodicProcessingStart", this.k), ("Duration", this.k), ("PartitionNameRef", this.s), ("Offset", this.k)), true) +
      this.emit("}\n", -1);
    
  }

  //Generates the code for partitionPort
  def generatePartitionPorts(nodes : Seq[Node], isSampling : Boolean) : String = nodes match {
    // If queuingPort and the last element of the list
    case x::xs if isSampling == false && xs == Nil =>
      this.emit("{ // Sampling\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("MaxMessageSize", this.k), ("Direction", this.s)), true) +      
      this.emit("}\n", -1);

    // If queuing port and not the last element of the list
    case x::xs if isSampling == false && xs != Nil =>
      this.emit("{ // Sampling\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("MaxMessageSize", this.k), ("Direction", this.s)), true) +
      this.emit("},\n", -1) +
      this.generatePartitionPorts(xs, isSampling);

    // If sampling port and the last element
    case x::xs if isSampling && xs == Nil => 
      this.emit("{ // Queuing\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("MaxMessageSize", this.k), ("Direction", this.s), ("MaxNbMessage", this.k)), true) +      
      this.emit("}\n", -1);

    // If sampling and not the last element
    case x::xs if isSampling && xs != Nil => 
      this.emit("{ //Queuing\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("MaxMessageSize", this.k), ("Direction", this.s), ("MaxNbMessage", this.k)), true) +      
      this.emit("},\n", -1) + 
      this.generatePartitionPorts(xs, isSampling);
  }

  // Recursively generate the memory region code 
  def generateMemoryRegion(nodes : Seq[Node]) : String = nodes match {
    // If we have a valid node, but there is no more valid nodes in the rest of the list
    case x::xs if xs == Nil => 
      this.emit("{ // Region\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("Type", this.s), ("Size", this.k), ("AccessRights", this.s)), true) +
      this.emitNodeAttributeOptional(x, List(("Address", this.k)), true) +
      this.emit("},\n", -1);
    // For all valid tags (Sometimes the attribute nodes are bloated) - and there are more valid nodes in the list
    case x::xs if xs != Nil => 
      this.emit("{ // Region\n") +
      this.emitNodeAttributesRequired(x, List(("Name", this.s), ("Type", this.s), ("Size", this.k), ("AccessRights", this.s)), true) +
      this.emitNodeAttributeOptional(x, List(("Address", this.k)), true) +
      this.emit("},\n", -1) +
      this.generateMemoryRegion(xs);
  }

  def emitNodeAttributeOptional(node : Node, attr : List[(String, (String) => String)], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => (if(this.checkAttributeValidity(x._1, node)) this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n", if (scoping) 1 else 0) else this.emit(f"{}, // ${x._1}\n")) + emitNodeAttributeOptional(node, xs)
    case x::xs if xs == Nil => if(this.checkAttributeValidity(x._1, node)) this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n") else this.emit(f"{}, // ${x._1}\n")
  }

  def emitNodeAttributesRequired(node : Node, attr : List[(String, (String) => String)], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n", if (scoping) 1 else 0) + emitNodeAttributeOptional(node, xs)
    case x::xs if xs == Nil => this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n")
    case _ => throw new Exception(f"The attribute: ${attr.head._1} is missing from your configuration");
  }

  def emitNodeAttributesRequiredNum(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${node.attribute(x).get.toString}, // ${x}\n", if (scoping) 1 else 0) + emitNodeAttributesRequiredNum(node, xs)
    case x::xs if xs == Nil => this.emit(f"${node.attribute(x).get.toString}, // ${x}\n")
    case _ => throw new Exception(f"The attribute: ${attr.head} is missing from your configuration");
  }

  def emitNodeAttributes(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${node.attribute(x).get};\n", if (scoping) 1 else 0) + emitNodeAttributes(node, xs)
    case x::xs if xs == Nil => this.emit(f"${node.attribute(x).get};\n")
  }

  def emitNodeAttributesWithIdentifier(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n", if (scoping) 1 else 0) + emitNodeAttributes(node, xs)
    case x::xs if xs == Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n")
  }

  // Check validity of an attribute (Many cases there are too many 'dummy' nodes in the tree)
  def checkAttributeValidity(tagName : String, node : Node) : Boolean = node.head.attribute(tagName) match {
    case None => false
    case _ => true
  }

  def emitIncludes(incls : List[String]) : String = incls match {
    case x::xs if xs != Nil => this.emit(f"#include '$x'\n") + this.emitIncludes(xs)
    case x::xs if xs == Nil => this.emit(f"#include '$x'\n\n")
  }

  def xmlLinesToList(filename : String) : List[Node] = {
    return XML.loadFile(filename).toList;
  }

  /**
     *  @brief A function that returns the input parameter
     *
     *  @details
     *      A dummy function used as a paramer, such that types can be passed as a 'null' value
     * 
     *  @param fun  Input String
     *  @return     The same input string
     */
  def k(string : String) : String = {
    string
  }

  /**
     *  @brief A function that returns the input parameter with '"' '"' 
     *
     *  @details
     *      A function used to append quotes in each end of a string
     *      - This is used as a parameter function
     * 
     *  @param fun  Input String
     *  @return     Input String with quotes
     */
  def s(string : String) : String = {
    '"' + string + '"'
  }
}