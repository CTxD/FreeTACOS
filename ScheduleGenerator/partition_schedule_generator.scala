import Validator.TimeEntity;

object PartitionScheduleGenerator {
  type CoreIterable = Array[Array[Array[Integer]]];
  type EntityIterable = Array[Array[Integer]];

  // Initialise indentation level value
  var level : Integer = 0;
  var INDENTATION_SPACE : Integer = 2;

  // Property for mapping id's to nameIdentifierRef
  var entities : List[TimeEntity] = List();

  // Initial function for starting the schedule generation
  def generateSchedule(scheduleTable : CoreIterable, entities : List[TimeEntity]) : String = {
    // Set properties
    this.entities = entities;

    // Begin traversing and generating the code
    var scheduleCpp : String = this.initCodeGeneration(scheduleTable);

    return scheduleCpp;
  }

  def initCodeGeneration(scheduleTable : CoreIterable) : String = {
    var emitString = this.emit("PartitionSchedule partitionSchedule = \n{\n");

    this.level += 1;
    emitString = emitString +
      this.traverseCores(scheduleTable);

    return emitString + this.emit("};", -1);
  }

  // Generate code for each core and further traverse
  def traverseCores(cores : CoreIterable) : String = cores.toList match {
    // If there are more cores to traverse
    case x::xs if xs != Nil => {
        var emitString = this.emit("{ // Core\n");
        this.level += 1;

        emitString = emitString +
          this.traversePartitions(x);

        emitString = emitString +
          this.emit("},\n", -1);

        return emitString + this.traverseCores(xs.toArray);
    }
    // If we are at the last core
    case x::xs if xs == Nil => {
      var emitString = this.emit("{ // Core\n");
      this.level += 1;

      emitString = emitString +
        this.traversePartitions(x);

      return emitString + this.emit("}\n", -1);
    }
    // Something went wrong
    case _ => throw new PartitionScheduleGeneratorException("Something went wrong generating code for the cores");
  }

  // Traverse and append partitions to cores
  def traversePartitions(partitions : EntityIterable) : String = partitions.toList match {
    // If the entitiy value is empty (just skip)
    case x::xs if x.head == null => ""

    // If there are more partitions to traverse
    case x::xs if xs != Nil && xs.head.head != null => {
      this.emit('"' + f"${this.mapIdToNameRef(x.head)}" + '"' + ", // PartitionNameRef \n") +
      this.traversePartitions(xs.toArray);
    }
    // If we are at the last partition
    case x::xs if xs == Nil || xs.head.head == null => {
      this.emit('"' + f"${this.mapIdToNameRef(x.head)}" + '"' + " // PartitionNameRef \n");
    }
    // Something went wrong
    case _ => throw new PartitionScheduleGeneratorException("Something went wrong generating code for the partitions");
  }

  // Mapping function from Integer value to entity PartitionNameRef value
  def mapIdToNameRef(id : Integer) : String = this.entities.filter(entity => entity.id == id).head.identifier;

  // Transform a string to the same string with indentation
  def emit(string : String, indent : Int = 0) : String = {
    // Match indentation settings
    indent match {
      case (-1) => this.level -= 1;
      case 1 => this.level += 1;
      case _ => {}
    }

    // Return indented string
    return " " * (this.INDENTATION_SPACE * this.level) + string;
  }

  class PartitionScheduleGeneratorException(message: String) extends Exception(message);
}
