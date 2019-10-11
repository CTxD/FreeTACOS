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
      return this.emit(f"Partition partitions[$partitionsSize] {\n") +
        this.generate(node.child) +
        this.emit("}\n");
    }
    // Generation for partitions and scoping rules.
    case "Partition" => {
      var partitionString = "";
      for(region <- node.child){
        var head = region.head;

        if(this.checkAttributeValidity("Identifier", region)){
          partitionString = partitionString + 
            this.emit("{\n") +
            this.emit(f"id = ${head.attribute("Identifier").get};\n", 1) +
            this.emit(f"name = ${head.attribute("Name").get};\n") +
            this.emit(f"affinity = ${head.attribute("Affinity").get};\n");
        }else if(this.checkAttributeValidity("Period", region)){
          partitionString = partitionString +
            this.emit(f"duration = ${head.attribute("Duration").get};\n") +
            this.emit(f"period = ${head.attribute("Period").get};\n")
        }
      }

      return partitionString + this.generate(node.child) + this.emit("}\n", -1);
    }
    // Parse memory region attributes
    case "MemoryRegions" => {
      // Loop through all MemoryRegion Tags
      val regionSize = node.child.filter(child => this.checkAttributeValidity("Type", child)).size;
      var emitString : String = this.emit(f"MemoryRegion memory_region[$regionSize] {\n");
      this.level += 1;

      return emitString +
        this.generateMemoryRegion(node.child) +
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
        queuingPorts = child.child.filter(child => this.checkAttributeValidity("MaxNbMessage", child.head)) ++ queuingPorts;
        samplingPorts = child.child.filter(child => this.checkAttributeValidity("MaxNbMessage", child.head) == false && this.checkAttributeValidity("MaxMessageSize", child.head)) ++ samplingPorts;
      }

      // Emit queuing ports
      var queuingString : String = "";
      if(queuingPorts.size > 0){
        queuingString = this.generatePartitionPorts(queuingPorts, true);

        emitString = emitString + this.emit(f"QueuePort queuingPartition[${queuingPorts.size}] {\n");
        this.level += 1;

        emitString = emitString +
          queuingString +
          this.emit("}\n", -1);
      }
      
      // Emit sampling ports
      var samplingString : String = "";
      if(samplingPorts.size > 0){
        samplingString = this.generatePartitionPorts(samplingPorts, false);

        emitString = emitString + this.emit(f"SamplingPort samplingPartition[${samplingPorts.size}] {\n");
        this.level += 1;

        emitString = emitString +
          samplingString + 
          this.emit("}\n", -1);
      }

      // Append end tag 
      return emitString;
    }
    // Partition end *** 

    case "Schedules" => {
      // Retrieve all Time Windows
      var partitionTimeWindows = node.child.filter(child => this.checkAttributeValidity("PeriodicProcessingStart", child));
      val partitionNum = partitionTimeWindows.size;

      // Emit initial Schedules stuff
      var emitString : String = this.emit(f"WindowSchedule window_schedule[$partitionNum] {\n");
      this.level += 1;

      emitString = emitString + 
        this.generatePartitionSchedules(partitionTimeWindows) +
        this.emit("}\n", -1);

      return emitString;
    }
    // TODO: Change this to "" when done
    case _ => node.head.label
  }
  
  def generatePartitionSchedules(nodes : Seq[Node]) : String = nodes match {
    // If we have more elements in the list
    case x::xs if xs != Nil => {
      val head = x;
      return this.emit("{\n") +
        this.emit(f"periodic_processing_start = ${head.attribute("PeriodicProcessingStart").get};\n", 1) +
        this.emit(f"duration = ${head.attribute("Duration").get};\n") +
        this.emit(f"partition_name_ref = ${head.attribute("PartitionNameRef").get};\n") +
        this.emit(f"offset = ${head.attribute("Offset").get};\n") +
        this.emit("},\n", -1) +
        this.generatePartitionSchedules(xs);
    }
    // If we are at the last element in the list
    case x::xs if xs == Nil => {
      val head = x;
      return this.emit("{\n") +
        this.emit(f"periodic_processing_start = ${head.attribute("PeriodicProcessingStart").get};\n", 1) +
        this.emit(f"duration = ${head.attribute("Duration").get};\n") +
        this.emit(f"partition_name_ref = ${head.attribute("PartitionNameRef").get};\n") +
        this.emit(f"offset = ${head.attribute("Offset").get};\n") +
        this.emit("}\n", -1);
    }
    case _ => "Ouch!"
  }

  //Generates the code for partitionPort
  def generatePartitionPorts(nodes : Seq[Node], isSampling : Boolean) : String = nodes match {
    // If queuingPort and the last element of the list
    case x::xs if isSampling == false && xs == Nil => {
      val head = x.head;
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"max_message_size = ${head.attribute("MaxMessageSize").get};\n") + 
      this.emit(f"direction = ${head.attribute("Direction").get};\n") + 
      this.emit("}\n", -1);
    }
    // If queuing port and not the last element of the list
    case x::xs if isSampling == false && xs != Nil => {
      val head = x.head;
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"max_message_size = ${head.attribute("MaxMessageSize").get};\n") + 
      this.emit(f"direction = ${head.attribute("Direction").get};\n") + 
      this.emit("},\n", -1) +
      this.generatePartitionPorts(xs, isSampling);
    }
    // If sampling port and the last element
    case x::xs if isSampling && xs == Nil => {
      val head = x.head;      
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"max_message_size = ${head.attribute("MaxMessageSize").get};\n") + 
      this.emit(f"max_nb_message = ${head.attribute("MaxNbMessage").get};\n") +
      this.emit(f"direction = ${head.attribute("Direction").get};\n") + 
      this.emit("}\n", -1);
    }
    // If sampling and not the last element
    case x::xs if isSampling && xs != Nil => {
      val head = x.head;      
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"max_message_size = ${head.attribute("MaxMessageSize").get};\n") + 
      this.emit(f"max_nb_message = ${head.attribute("MaxNbMessage").get};\n") +
      this.emit(f"direction = ${head.attribute("Direction").get};\n") + 
      this.emit("},\n", -1) + 
      this.generatePartitionPorts(xs, isSampling);
    }
    // Something went wrong - This shouldn't happen (like, ever)
    case _ => "Ouch!"
  }

  // Recursively generate the memory region code 
  def generateMemoryRegion(nodes : Seq[Node]) : String = nodes match {
    // If we have a valid node, but there is no more valid nodes in the rest of the list
    case x::xs if xs.filter(elem => this.checkAttributeValidity("Type", elem)) == Nil && this.checkAttributeValidity("Type", x) => {
      val head = x.head;
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"type = ${head.attribute("Type").get};\n") +
      this.emit(f"size = ${head.attribute("Size").get};\n") +
      this.emit(f"access_rights = ${head.attribute("AccessRights").get};\n") +
      this.emit("}\n", -1);
    }
    // For all valid tags (Sometimes the attribute nodes are bloated) - and there are more valid nodes in the list
    case x::xs if this.checkAttributeValidity("Type", x) && xs.filter(elem => this.checkAttributeValidity("Type", elem)) != Nil => {
      val head = x.head;
      this.emit("{\n") +
      this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
      this.emit(f"type = ${head.attribute("Type").get};\n") +
      this.emit(f"size = ${head.attribute("Size").get};\n") +
      this.emit(f"access_rights = ${head.attribute("AccessRights").get};\n") +
      this.emit("},\n", -1) +
      this.generateMemoryRegion(xs);
    }
    case x::xs if xs == Nil => ""
    case x::xs if this.checkAttributeValidity("Type", x) == false => this.generateMemoryRegion(xs)
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