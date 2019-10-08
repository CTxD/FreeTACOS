import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter}

object ScheduleGenerator{
  var level : Int = 0;

  def main(args: Array[String]): Unit = {
    // Set indentation level to 0.
    val configName : String = "exampleschedule.xml";

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
    case "MODULE" => {
      return (
        this.emit("#include \"a.h\"\n") +
        this.emit("#include \"b.h\"\n\n")
      ) + this.generate(node.child);
    }
    // Partition Specifics here - Get the number of subpartitions for allocating the size of the array
    case "Partitions" => {
      return this.emit(f"Partition partitions[${node.child.filter(child => child.head.label == "Partition").size}] {\n") +
        this.generate(node.child) +
        this.emit("}");
    
    }
    case "Partition" => {
      var partitionString = "";
      for(region <- node.child){
        var head = region.head;

        if(this.checkAttributeValidity("Identifier", region)){
          partitionString = partitionString + 
            this.emit("{\n", 1) +
            this.emit(f"id = ${head.attribute("Identifier").get};\n", 1) +
            this.emit(f"name = ${head.attribute("Name").get};\n");
        }else if(this.checkAttributeValidity("Period", region)){
          partitionString = partitionString +
            this.emit(f"duration = ${head.attribute("Duration").get};\n") +
            this.emit(f"period = ${head.attribute("Period").get};\n")
        }
      }

      return partitionString + this.generate(node.child) + "\n}";
    }
    // Parse memory region attributes
    case "MemoryRegions" => {
      // Loop through all MemoryRegion Tags
      val regionSize = node.child.filter(child => this.checkAttributeValidity("Type", child)).size;
      var memoryString = this.emit(f"MemoryRegion memory_region[$regionSize] {\n");

      var loopCount = 0;
      for(region <- node.child){
        // Check node validity
        if(this.checkAttributeValidity("Type", region)){
          loopCount += 1;
          var head = region.head;

          // Append String with attributes
          memoryString = memoryString + 
            this.emit("{\n", 1) +
            this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
            this.emit(f"type = ${head.attribute("Type").get};\n") +
            this.emit(f"size = ${head.attribute("Size").get};\n") +
            this.emit(f"access_rights = ${head.attribute("AccessRights").get};\n") +
            this.emit("}", -1);

          // Check for exceeding or last element
          if(loopCount >= regionSize) 
            memoryString = memoryString + this.emit("\n}\n", -1);
          else 
            memoryString = memoryString + this.emit(",\n", -1);
        }
        
      }

      return memoryString
    }
    case "PartitionPorts" => {
      return this.emit(f"partition_ports[${node.child.filter(elem => elem.head.label == "PartitionPort").size}] {\n") +
        generate(node.child) +
        this.emit("}\n");
    }
    case "PartitionPort" => {
      var partitionString = "";
      for(region <- node.child){
        var head = region.head;
        if(this.checkAttributeValidity("MaxMessageSize", region)){
          partitionString = partitionString + 
            this.emit("{\n", 1) +
            this.emit(f"name = ${head.attribute("Name").get};\n", 1) +
            this.emit(f"max_message_size = ${head.attribute("MaxMessageSize").get};\n") + 
            this.emit(f"direction = ${head.attribute("Direction").get};\n") + 
            this.emit("}\n", -1);
        }


      }

      return partitionString;
    }
    // Partition end
    case _ => node.head.label
  }

  def generatePartition(nodes : Seq[Node]) : String = nodes.head.label match {
    case "Partition" => "Partition Start[] {"

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