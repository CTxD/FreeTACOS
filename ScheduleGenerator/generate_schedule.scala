import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter}
import Validator.Validator;

object ScheduleGenerator{
  var level : Int = 0;
  var validator : Validator = new Validator();

  def main(args: Array[String]): Unit = {
    var configName : String = args.filter(arg => arg.split("=").head == "--filename").head.split("=").last;

    try{
      println("Fetching xml file");
      var lines = this.xmlLinesToList(configName);

      println("Generating code");
      val generatedString = generate(lines);

      // validator will throw an exception if the check is unsuccessful
      println("Validating schedule configuration");
      //this.validator.checkScheduleValidity();
      println("Validation succeeded")

      println("Writing to file");
      val writer = new PrintWriter(new File("../src/kernel/config.cpp" ));
      writer.write(generatedString);
      writer.close(); 
      
      println("Success");
    } catch {
      case err : NoClassDefFoundError => {
        println("Class Not Found Exception");
      }
      case err : FileNotFoundException => {
        println("Input file not found");
      }
      case err : Exception => {
        println(err);
      }
      case _ : Throwable => {
        println("Some unexpected error happened");
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
        "arinc_module.h",
        "channel.h", 
        "error_action.h",
        "error_level.h",
        "general_types.h",
        "memory_requirements.h",
        "module_hm_table.h",
        "multipartition_hm_table.h",
        "partition.h",
        "partition_hm_table.h",
        "partition_memory.h",
        "port_mapping.h",
        "port_type.h",
        "process.h",
        "pseudo_standard_partitions.h",
        "schedule.h",
        "system_state_entry.h",
        "apex_blackboard.h",
        "apex_queuing_port.h",
        "apex_sampling_port.h",
        "apex_buffer.h",
        "apex_error.h",
        "apex_event.h",
        "apex_partition.h",
        "apex_process.h",
        "apex_queuing_port.h",
        "apex_sampling_port.h",
        "apex_semaphore.h",
        "apex_time.h",
        "apex_types.h"
      ));
      
      var emitString : String = includes + this.emit("ArincModule arincModule {\n");
      
      this.level += 1;
      emitString = emitString +
        this.emitNodeAttributeOptional(node, List(
          ("Name", this.s), 
          ("ModuleVersion", this.k), 
          ("moduleId", this.k)), 
          true);

      return emitString +
        this.generate(node.child) +
        this.emit("};\n", -1);
    }
    // Partition Specifics here - Get the number of subpartitions for allocating the size of the array
    case "Partitions" => {
      var emitString : String = this.emit("{ // Partitions\n");
      this.level += 1;
      
      return emitString +
        this.generate(node.child) +
        this.emit("},\n", -1);
    }
    // Generation for partitions and scoping rules.
    case "Partition" => {
      var partitionString = "";
      for(region <- node.child) {
        var head = region.head;

        if(this.checkAttributeValidity("Identifier", region)){
          // Populate the partition name to the validator
          this.validator.populatePartitionIdentifier(this.retrieveNodeAttributeString(region, "Name"));

          // Append emit string with partition definition info
          partitionString = partitionString + 
            this.emit("{ // Partition\n") +
            this.emitNodeAttributesRequired(head, List(
              ("Identifier", this.k), 
              ("Affinity", this.k)), 
              true) +
            this.emitNodeAttributeOptional(head, List(("Name", this.s)));
        }else if(this.checkAttributeValidity("Period", region)){
          // Populate the remaining attributes to the validator
          this.validator.populatePartitionRemainder(
            this.retrieveNodeAttributeString(region, "Period").toInt,
            this.retrieveNodeAttributeString(region, "Duration").toInt
          );

          // Append emit string with partition attributes
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
        this.emit("},\n", -1);
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
          this.emit("},\n", -1);
      }else{
        emitString = emitString + this.emit("{},\n");
      }
      
      // Emit sampling ports
      var samplingString : String = "";
      if(samplingPorts.size > 0){
        emitString = emitString + this.emit(f"{ // Sampling\n");
        this.level += 1;

        emitString = emitString +
          this.generatePartitionPorts(samplingPorts, false) +
          this.emit("}\n", -1);
      }else{
        emitString = emitString + this.emit("{}\n");
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

      return emitString + this.emit("},\n", -1);
    }

    // Schedules end ******
    case "HealthMonitoring" => {
      // Initial code gen
      //var emitString : String = this.emit("{ // Health Monitor\n");
      //this.level += 1

      // Generate for all SystemErrors
      var emitString = this.generate(node.child);

      var multiPartitions = node.child.filter(child => child.head.label == "MultiPartitionHM");
      emitString = emitString + 
        this.emit(f"{ // MultiPartitionHM\n");
      this.level += 1;
      emitString = emitString +
        this.generateMultipartitions(multiPartitions) +
        this.emit("},\n", -1);

      // Handle generation for moduleHM, partitionHM and multiPartitionHm, since need of context ->
      var moduleHms = node.child.filter(child => child.head.label == "ModuleHM");
      emitString = emitString +
        this.emit(f"{ // ModulesHM\n");
      this.level += 1;
      emitString = emitString +
        this.generateModuleHM(moduleHms) +
        this.emit(f"},\n", -1);

      var partitionsHM = node.child.filter(child => child.head.label == "PartitionHM");
      emitString = emitString +
        this.emit(f"{ // PartitionHM\n");
        this.level += 1;
        emitString = emitString + 
          this.generatePartitionsHM(partitionsHM) +
          this.emit("}\n", -1);

      return emitString;
    }

    case "SystemErrors" => {
      // Generate code for systemErrors w/ scoping and indentation
      val errors = node.child.filter(child => this.checkAttributeValidity("ErrorIdentifier", child));
      var emitString = this.emit(f"{ // SystemError\n");
      this.level += 1;

      emitString = emitString + 
      this.generateSystemErrors(errors) +
      this.emit("},\n", -1);

      return emitString;
    }

    case _ => ""
  }

  def generatePartitionsHM(nodes : Seq[Node]) : String = nodes match {
    case x::xs if xs != Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString = this.emit("{ // PartitionsHM\n");

      emitString = emitString +
        this.emitNodeAttributesRequired(x, List(("TableName", this.s), ("MultiPartitionHMTableNameRef", this.s)), true) +
        this.emit(f"{ // SystemError\n");

      this.level += 1;
      emitString = emitString +
        this.generateErrorActions(errorActions, isPHM = true) +
        this.emit("}\n", -1);
      
      return emitString + this.emit("},\n", -1) + this.generatePartitionsHM(xs);
    }
    case x::xs if xs == Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));
      var emitString = this.emit("{ // PartitionHM\n");

      emitString = emitString +
        this.emitNodeAttributesRequired(x, List(
          ("TableName", this.s), 
          ("MultiPartitionHMTableNameRef", this.s)), 
          true) +
          this.emit(f"{ // SystemError\n");

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
        this.emitNodeAttributesRequired(x, List(("TableName", this.s)), true) +
        this.emit(f"{ // SystemError\n");
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
        this.emitNodeAttributesRequired(x, List(("TableName", this.s)), true) +
        this.emit(f"{ // SystemError\n");
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

      var emitString : String = this.emit("{ // ModuleHM\n") +
        this.emitNodeAttributesRequired(x, List(
          ("StateIdentifier", this.k), 
          ("Description", this.s)), 
          true) +
        this.emit(f"{ // ErrorAction\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, true) +
        this.emit("}\n", -1);

      return emitString + this.emit("},\n", -1) + this.generateModuleHM(xs);
    }
    // If this is the last node in the sequence
    case x::xs if xs == Nil => {
      val errorActions = x.child.filter(child => this.checkAttributeValidity("ErrorIdentifierRef", child));

      var emitString : String = this.emit("{ // ModuleHM\n") +
        this.emitNodeAttributesRequired(x, List(
          ("StateIdentifier", this.k), 
          ("Description", this.s)), 
          true) +
          this.emit(f"{ // ErrorAction\n");
      this.level += 1;

      emitString = emitString +
        this.generateErrorActions(errorActions, true) +
        this.emit("}\n", -1);

      return emitString + this.emit("}\n", -1);
    }
  }

  def generateErrorActions(nodes : Seq[Node], isHM : Boolean = false, isMP : Boolean = false, isPHM : Boolean = false) : String = nodes match {
    case x::xs if xs != Nil && isPHM => {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(
        ("ErrorIdentifierRef", this.k), 
        ("PartitionRecoveryAction", this.mapPartitionRecoveryAction), 
        ("ErrorLevel", this.mapErrorLevel), 
        ("ErrorCode", this.mapErrorCode)), 
        true) +
      this.emit("},\n", -1) +
      this.generateErrorActions(xs, isPHM = true);
    }
    case x::xs if xs == Nil && isPHM => {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(
        ("ErrorIdentifierRef", this.k), 
        ("PartitionRecoveryAction", this.mapPartitionRecoveryAction), 
        ("ErrorLevel", this.mapErrorLevel), 
        ("ErrorCode", this.mapErrorCode)), 
        true) +
      this.emit("}\n", -1);
    }
    // If there are more nodes in the sequence
    case x::xs if xs != Nil && isHM=> {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(("ErrorIdentifierRef", this.k), 
      ("ModuleRecoveryAction", this.mapModuleRecoveryAction)), 
      true) +
      this.emit("},\n", -1) +
      this.generateErrorActions(xs, true);
    }
    // If this is the last node in the sequence
    case x::xs if xs == Nil && isHM => {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(
        ("ErrorIdentifierRef", this.k), 
        ("ModuleRecoveryAction", this.mapModuleRecoveryAction)), 
        true) +
      this.emit("}\n", -1);
    }
    case x::xs if xs != Nil && isMP => {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(
        ("ErrorIdentifierRef", this.k), 
        ("ErrorLevel", this.mapErrorLevel)), 
        true) +
        this.emitNodeAttributeOptional(x, List(("ErrorAction", this.mapModuleRecoveryAction))) +
        this.emit("},\n", -1) +
        this.generateErrorActions(xs, isMP = true);
    }
    case x::xs if xs == Nil && isMP => {
      this.emit("{ // ErrorAction\n") +
      this.emitNodeAttributesRequired(x, List(
        ("ErrorIdentifierRef", this.k), 
        ("ErrorLevel", this.mapErrorLevel)), 
        true) +
      this.emitNodeAttributeOptional(x, List(
        ("ErrorAction", this.mapModuleRecoveryAction))) +
      this.emit("}\n", -1);
    }
  }

  def generateSystemErrors(nodes : Seq[Node]) : String = nodes match {
    // If we have more nodes in the sequence
    case x::xs if xs != Nil => {
      return this.emit("{\n") +
        this.emitNodeAttributesRequired(x, List(
          ("ErrorIdentifier", this.k), 
          ("Description", this.s)), 
          true) +
          this.emit("},\n", -1) +
          this.generateSystemErrors(xs);
    }
    // If we are at the very last element
    case x::xs if xs == Nil => {
      return this.emit("{\n") +
        this.emitNodeAttributesRequired(x, List(
          ("ErrorIdentifier", this.k), 
          ("Description", this.s)), 
          true) +
        this.emit("}\n", -1);
    }
  }
  
  def generatePartitionSchedules(nodes : Seq[Node]) : String = nodes match {
    // If we have more elements in the list
    case x::xs if xs != Nil => {
      // Create a new TimeSchedule object for the validator
      if(this.checkAttributeValidity("PartitionNameRef", x)){
        this.validator.appendSchedule(
          this.retrieveNodeAttributeString(x, "PartitionNameRef"),
          this.retrieveNodeAttributeString(x, "Duration").toInt,
          this.retrieveNodeAttributeString(x, "Offset").toInt
        );
      }

      // Append emit string
      return this.emit("{\n") +
      this.emitNodeAttributesRequired(x, List(
        ("PeriodicProcessingStart", this.k), 
        ("Duration", this.k), 
        ("PartitionNameRef", this.s), 
        ("Offset", this.k)), 
        true) +
      this.emit("},\n", -1) +
      this.generatePartitionSchedules(xs);
    }
    
    // If we are at the last element in the list
    case x::xs if xs == Nil => {
      // Create a new TimeSchedule object for the validator
      if(this.checkAttributeValidity("PartitionNameRef", x)){
        this.validator.appendSchedule(
          this.retrieveNodeAttributeString(x, "PartitionNameRef"),
          this.retrieveNodeAttributeString(x, "Duration").toInt,
          this.retrieveNodeAttributeString(x, "Offset").toInt
        );
      }

      // Append the last element to the emit string
      return this.emit("{\n") +
      this.emitNodeAttributesRequired(x, List(
        ("PeriodicProcessingStart", this.k), 
        ("Duration", this.k), 
        ("PartitionNameRef", this.s), 
        ("Offset", this.k)), true) +
        this.emit("}\n", -1);
    }
  }

  //Generates the code for partitionPort
  def generatePartitionPorts(nodes : Seq[Node], isSampling : Boolean) : String = nodes match {
    // If queuingPort and the last element of the list
    case x::xs if isSampling == false && xs == Nil =>
      this.emit("{ // Sampling\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("MaxMessageSize", this.k), 
        ("Direction", this.mapDirectionType)), true) +
      this.emitNodeAttributeOptional(x, List(("RefreshRate", this.s))) +
      this.emit("}\n", -1);

    // If queuing port and not the last element of the list
    case x::xs if isSampling == false && xs != Nil =>
      this.emit("{ // Sampling\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("MaxMessageSize", this.k), 
        ("Direction", this.mapDirectionType)), true) +
      this.emitNodeAttributeOptional(x, List(("RefreshRate", this.s))) +
      this.emit("},\n", -1) +
      this.generatePartitionPorts(xs, isSampling);

    // If sampling port and the last element
    case x::xs if isSampling && xs == Nil => 
      this.emit("{ // Queuing\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("MaxMessageSize", this.k), 
        ("Direction", this.mapDirectionType), 
        ("MaxNbMessage", this.k)), true) +      
      this.emit("}\n", -1);

    // If sampling and not the last element
    case x::xs if isSampling && xs != Nil => 
      this.emit("{ //Queuing\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("MaxMessageSize", this.k), 
        ("Direction", this.mapDirectionType), 
        ("MaxNbMessage", this.k)), true) +      
      this.emit("},\n", -1) + 
      this.generatePartitionPorts(xs, isSampling);
  }

  // Recursively generate the memory region code 
  def generateMemoryRegion(nodes : Seq[Node]) : String = nodes match {
    // If we have a valid node, but there is no more valid nodes in the rest of the list
    case x::xs if xs == Nil => 
      this.emit("{ // Region\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("Type", this.mapMemoryType), 
        ("Size", this.k), 
        ("AccessRights", this.mapMemoryAccess)), true) +
      this.emitNodeAttributeOptional(x, List(("Address", this.k)), true) +
      this.emit("}\n", -1);
    // For all valid tags (Sometimes the attribute nodes are bloated) - and there are more valid nodes in the list
    case x::xs if xs != Nil => 
      this.emit("{ // Region\n") +
      this.emitNodeAttributesRequired(x, List(
        ("Name", this.s), 
        ("Type", this.mapMemoryType), 
        ("Size", this.k), 
        ("AccessRights", this.mapMemoryAccess)), true) +
      this.emitNodeAttributeOptional(x, List(("Address", this.k)), true) +
      this.emit("},\n", -1) +
      this.generateMemoryRegion(xs);
  }

  def retrieveNodeAttributeString(node : Node, attr : String) : String = attr match {
    case x if this.checkAttributeValidity(x, node) => node.attribute(attr).get.toString;
    case _ => throw new Exception(f"Attribute $attr can not be found");
  }

  // Emits optional attributes (if not found emit '{}')
  def emitNodeAttributeOptional(node : Node, attr : List[(String, (String) => String)], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => {
      if(this.checkAttributeValidity(x._1, node)) 
        return this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n", if (scoping) 1 else 0) + emitNodeAttributeOptional(node, xs);
      else 
        return this.emit(f"{}, // ${x._1}\n") + emitNodeAttributeOptional(node, xs);
    }
    case x::xs if xs == Nil => {
      if(this.checkAttributeValidity(x._1, node)) 
        return this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n");
      else 
        return this.emit(f"{}, // ${x._1}\n");
    }
  }

  // Emits required attributes (If not found, throw an exception)
  def emitNodeAttributesRequired(node : Node, attr : List[(String, (String) => String)], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n", if (scoping) 1 else 0) + emitNodeAttributeOptional(node, xs)
    case x::xs if xs == Nil => this.emit(f"${x._2(node.attribute(x._1).get.toString)}, // ${x._1}\n")
    case _ => throw new Exception(f"The attribute: ${attr.head._1} is missing from your configuration");
  }

  // Function that emits attributes as numerical type
  def emitNodeAttributesRequiredNum(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${node.attribute(x).get.toString}, // ${x}\n", if (scoping) 1 else 0) + emitNodeAttributesRequiredNum(node, xs)
    case x::xs if xs == Nil => this.emit(f"${node.attribute(x).get.toString}, // ${x}\n")
    case _ => throw new Exception(f"The attribute: ${attr.head} is missing from your configuration");
  }

  // Function to emit node attributes without any other information 
  def emitNodeAttributes(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${node.attribute(x).get};\n", if (scoping) 1 else 0) + emitNodeAttributes(node, xs)
    case x::xs if xs == Nil => this.emit(f"${node.attribute(x).get};\n")
  }

  // Emits node without a mapping function, but instead utilises the identifier
  def emitNodeAttributesWithIdentifier(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n", if (scoping) 1 else 0) + emitNodeAttributes(node, xs)
    case x::xs if xs == Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n")
  }

  // Check validity of an attribute (Many cases there are too many 'dummy' nodes in the tree)
  def checkAttributeValidity(tagName : String, node : Node) : Boolean = node.head.attribute(tagName) match {
    case None => false
    case _ => true
  }

  // Emit function specific for the includes
  def emitIncludes(incls : List[String]) : String = incls match {
    case x::xs if xs != Nil => this.emit(f"#include ${this.sInclude(x)} \n") + this.emitIncludes(xs)
    case x::xs if xs == Nil => this.emit(f"#include ${this.sInclude(x)}\n\n")
  }

  // Mapping function for error code attributes
  def mapErrorCode(code : String) : String = code match {
    case "DEADLINE_MISSED" => "ERROR_CODE_TYPE::DEADLINE_MISSED"
    case "APPLICATION_ERROR" => "ERROR_CODE_TYPE::APPLICATION_ERROR"
    case "NUMERIC_ERROR" => "ERROR_CODE_TYPE::NUMERIC_ERROR"
    case "ILLEGAL_REQUEST" => "ERROR_CODE_TYPE::ILLEGAL_REQUEST"
    case "STACK_OVERFLOW" => "ERROR_CODE_TYPE::STACK_OVERFLOW"
    case "MEMORY_VIOLATION" => "ERROR_CODE_TYPE::MEMORY_VIOLATION"
    case "HARDWARE_FAULT" => "ERROR_CODE_TYPE::HARDWARE_FAULT"
    case "POWER_FAILURE" => "ERROR_CODE_TYPE::POWER_FAILURE"
    case _   => throw new Exception(f"$code is not a supported ErrorCode")
  }

  // Mapping function for error level attributes
  def mapErrorLevel(error : String) : String = error match {
    case "MODULE" => "ERROR_LEVEL_TYPE::MODULE"
    case "PARTITION" => "ERROR_LEVEL_TYPE::PARTITION"
    case "PROCESS" => "ERROR_LEVEL_TYPE::PROCESS"
    case _ => throw new Exception(f"$error is not a support ErrorLevel")
  }

  // Mapping function for partition recovery action attributes
  def mapPartitionRecoveryAction(action : String) : String = action match {
    case "IDLE" => "PARTITION_RECOVERY_ACTION_TYPE::IDLE"
    case "COLD_RESTART" => "PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART"
    case "WARM_RESTART" => "PARTITION_RECOVERY_ACTION_TYPE::WARM_RESTART"
    case "NORMAL" => "PARTITION_RECOVERY_ACTION_TYPE::NORMAL"
    case _      => throw new Exception(f"$action is not a supported Partition Recovery Action type")
  }

  // Mapping function for module recovery action attributes
  def mapModuleRecoveryAction(action : String) : String = action match {
    case "IGNORE" => "MODULE_RECOVERY_ACTION_TYPE::IGNORE"
    case "SHUTDOWN" => "MODULE_RECOVERY_ACTION_TYPE::SHUTDOWN"
    case "RESET" => "MODULE_RECOVERY_ACTION_TYPE::RESET"
    case _ => throw new Exception(f"$action is not a support recovery action")
  }

  // Mapping function for direction type attributes
  def mapDirectionType(direction : String) : String = direction match {
    case "SOURCE" => "PORT_DIRECTION_TYPE::SOURCE"
    case "DESTINATION" => "PORT_DIRECTION_TYPE::DESTINATION"
    case _ => throw new Exception(f"$direction is not supported as a direction type")
  }

  // Mapping function for memory type attributes
  def mapMemoryType(memType : String) : String = memType match {
    case "Flash" => "memory_region_t::FLASH"
    case "RAM" => "memory_region_t::RAM"
    case "Input/Output" => "memory_region_t::INPUT_OUTPUT"
    case _ => throw new Exception(f"$memType is not supported for MemoryRegions")
  }

  // Mapping function for memory access attributes
  def mapMemoryAccess(access : String) : String = access match {
    case "READ_ONLY" => "memory_access_t::READ_ONLY"
    case "READ_WRITE" => "memory_access_t::READ_WRITE"
    case _ => throw new Exception(f"$access is not supported for MemoryAccess")
  }

  // Function for reading xml file
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
    "{" + '"' + string + '"' + "}"
  }

  // String converter function for includes
  def sInclude(string : String) : String = {
    '<' + string + '>'
  }
}