import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter}

object ScheduleGenerator{
  var level : Int = 0;

  def main(args: Array[String]): Unit = {
    val configName : String = "configuration.xml";

    try{
      val lines = this.xmlLinesToList(configName);
      val generatedString = generate(lines);
      println(generatedString);
      val writer = new PrintWriter(new File("gen.cpp" ));
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
      return (
        this.emit("#include \"a.h\"\n") +
        this.emit("#include \"b.h\"\n\n")
      ) + this.generate(node.child);
    }
    // Partition Specifics here - Get the number of subpartitions for allocating the size of the array
    case "Partitions" => {
      val partitionsSize = node.child.filter(child => child.head.label == "Partition").size;
      var emitString : String = this.emit(f"Partition partitions[$partitionsSize] {\n");
      this.level += 1;
      
      return emitString +
        this.generate(node.child) +
        this.emit("}\n", -1);
    }
    // Generation for partitions and scoping rules.
    case "Partition" => {
      var partitionString = "";
      for(region <- node.child){
        var head = region.head;

        if(this.checkAttributeValidity("Identifier", region)){
          partitionString = partitionString + 
            this.emit("{\n") +
            this.emitNodeAttributes(head, List("Identifier", "Name", "Affinity"), true);
        }else if(this.checkAttributeValidity("Period", region)){
          partitionString = partitionString +
            this.emitNodeAttributes(head, List("Duration", "Period"));
        }
      }

      return partitionString + this.generate(node.child) + this.emit("}\n", -1);
    }
    // Parse memory region attributes
    case "MemoryRegions" => {
      // Loop through all MemoryRegion Tags
      val regions = node.child.filter(child => this.checkAttributeValidity("Type", child));
      var emitString : String = this.emit(f"MemoryRegion memory_region[${regions.size}] {\n");
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
        emitString = emitString + this.emit(f"QueuePort queuingPartition[${queuingPorts.size}] {\n");
        this.level += 1;

        emitString = emitString +
          this.generatePartitionPorts(queuingPorts, true) +
          this.emit("}\n", -1);
      }
      
      // Emit sampling ports
      var samplingString : String = "";
      if(samplingPorts.size > 0){
        emitString = emitString + this.emit(f"SamplingPort samplingPartition[${samplingPorts.size}] {\n");
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
      var emitString : String = this.emit(f"WindowSchedule window_schedule[$partitionNum] {\n");
      this.level += 1;

      // Emit all the partitionWindows
      emitString = emitString + 
        this.generatePartitionSchedules(partitionTimeWindows) +
        this.emit("}\n", -1);

      return emitString;
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
    case x::xs if xs != Nil => {
      return this.emit("{\n") +
        this.emitNodeAttributes(x, List("PeriodicProcessingStart", "Duration", "PartitionNameRef", "Offset"), true) +
        this.emit("},\n", -1) +
        this.generatePartitionSchedules(xs);
    }
    // If we are at the last element in the list
    case x::xs if xs == Nil => {
      val head = x;
      return this.emit("{\n") +
        this.emitNodeAttributes(x, List("PeriodicProcessingStart", "Duration", "PartitionNameRef", "Offset"), true) +
        this.emit("}\n", -1);
    }
  }

  //Generates the code for partitionPort
  def generatePartitionPorts(nodes : Seq[Node], isSampling : Boolean) : String = nodes match {
    // If queuingPort and the last element of the list
    case x::xs if isSampling == false && xs == Nil => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "MaxMessageSize", "Direction"), true) +
      this.emit("}\n", -1);
    }
    // If queuing port and not the last element of the list
    case x::xs if isSampling == false && xs != Nil => {
      val head = x.head;
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "MaxMessageSize", "Direction"), true) +
      this.emit("},\n", -1) +
      this.generatePartitionPorts(xs, isSampling);
    }
    // If sampling port and the last element
    case x::xs if isSampling && xs == Nil => {
      val head = x.head;      
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "MaxMessageSize", "Direction", "MaxNbMessage"), true) +
      this.emit("}\n", -1);
    }
    // If sampling and not the last element
    case x::xs if isSampling && xs != Nil => {
      val head = x.head;      
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "MaxMessageSize", "Direction", "MaxNbMessage"), true) +
      this.emit("},\n", -1) + 
      this.generatePartitionPorts(xs, isSampling);
    }
  }

  // Recursively generate the memory region code 
  def generateMemoryRegion(nodes : Seq[Node]) : String = nodes match {
    // If we have a valid node, but there is no more valid nodes in the rest of the list
    case x::xs if xs == Nil => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "Type", "Size", "AccessRights"), true) +
      this.emit("}\n", -1);
    }
    // For all valid tags (Sometimes the attribute nodes are bloated) - and there are more valid nodes in the list
    case x::xs if xs != Nil => {
      this.emit("{\n") +
      this.emitNodeAttributes(x, List("Name", "Type", "Size", "AccessRights"), true) +
      this.emit("},\n", -1) +
      this.generateMemoryRegion(xs);
    }
  }

  def emitNodeAttributes(node : Node, attr : List[String], scoping : Boolean = false) : String = attr match {
    case x::xs if xs != Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n", if (scoping) 1 else 0) + emitNodeAttributes(node, xs, false)
    case x::xs if xs == Nil => this.emit(f"${x.toLowerCase} = ${node.attribute(x).get};\n")
  }

  // Check validity of an attribute (Many cases there are too many 'dummy' nodes in the tree)
  def checkAttributeValidity(tagName : String, node : Node) : Boolean = node.head.attribute(tagName) match {
    case None => false
    case _ => true
  }

  def xmlLinesToList(filename : String) : List[Node] = {
    return XML.loadFile(filename).toList;
  }
}