import Validator.TimeEntity;

object PartitionScheduleGenerator {
  type CoreIterable = Array[Array[Array[Integer]]];
  type EntityIterable = Array[Array[Integer]];

  // Initialise indentation level value
  var level: Integer = 0;
  var INDENTATION_SPACE: Integer = 2;

  // Property for mapping id's to nameIdentifierRef
  var entities: List[TimeEntity] = List();

  // Initial function for starting the schedule generation
  def generateSchedule(scheduleTable: CoreIterable,
                       entities: List[TimeEntity]): String = {
    // Set properties
    this.entities = entities;

    // Begin traversing and generating the code
    var scheduleCpp: String = this.initCodeGeneration(scheduleTable);

    return scheduleCpp;
  }

  // Initial code generation function
  def initCodeGeneration(scheduleTable: CoreIterable): String = {
    // Emit includes first
    var emitString =
      this.emit(this.mapStringToInclude("core_schedule.hpp")) +
      "\n\n";

    emitString = emitString + this.emit("CoreSchedule coreSchedule = \n{ // CoreSchedule \n");

    emitString = emitString +
      this.emit("{\n", 1);

    this.level += 1;
    emitString = emitString +
      this.traverseCores(scheduleTable) +
      this.emit("}\n", -1);

    return emitString + this.emit("};", -1);
  }

  // Generate code for each core and further traverse
  def traverseCores(cores: CoreIterable): String = cores.toList match {
    // If there are more cores to traverse
    case x :: xs if xs != Nil => {
      var emitString = this.emit("{ // Core\n");
      this.level += 1;

      emitString = emitString +
        this.traversePartitions(x);

      emitString = emitString +
        this.emit("},\n", -1);

      return emitString + this.traverseCores(xs.toArray);
    }
    // If we are at the last core
    case x :: xs if xs == Nil => {
      var emitString = this.emit("{ // Core\n");
      this.level += 1;

      emitString = emitString +
        this.traversePartitions(x);

      return emitString + this.emit("}\n", -1);
    }
    // Something went wrong
    case _ =>
      throw new PartitionScheduleGeneratorException(
        "Something went wrong generating code for the cores");
  }

  // Traverse and append partitions to cores
  def traversePartitions(partitions: EntityIterable): String =
    partitions.toList match {
      // If the entitiy value is empty (just skip)
      case x :: xs if x.head == null => ""

      // If there are more partitions to traverse
      case x :: xs if xs != Nil && xs.head.head != null => {
        val partition : TimeEntity = this.mapIdToPartitionO(x.head);

        var emitString = this.emit("{ // Partition \n") +
          this.emitPartitionValues(partition) +
          this.emit("},\n", -1);

        return emitString + this.traversePartitions(xs.toArray);
      }


      // If we are at the last partition
      case x :: xs if xs == Nil || xs.head.head == null => {
        val partition : TimeEntity = this.mapIdToPartitionO(x.head);

        var emitString = this.emit("{ // Partition \n") +
          this.emitPartitionValues(partition) +
          this.emit("}\n", -1);

        return emitString;
      }

      // Something went wrong
      case _ =>
        throw new PartitionScheduleGeneratorException(
          "Something went wrong generating code for the partitions");
  }

  def emitPartitionValues(partition : TimeEntity) : String = {
    this.emit("{ // PartitionValues \n", 1) +
    this.emit(f"${partition.periodicProcessingStart}, // PeriodicProcessingStart \n", 1) +
    this.emit(f"${partition.duration}, // Duration \n") +
    this.emit(f"${this.mapStringToNameT(partition.identifier)}, // PartitionNameRef \n") +
    this.emit(f"${partition.offset}, // Offset \n") +
    this.emit(f"${partition.period}, // Period \n") +
    this.emit(f"${partition.affinity} // Affinity \n") +
    this.emit("}\n", -1);
  }

  def mapStringToUsingNameSpace(string : String) : String = "using namespace " + string + ";";

  def mapStringToInclude(string : String) : String = "#include " + '"' + string + '"';

  def mapStringToNameT(string : String) : String = "{" + '"' + string + '"' + "}";

  def mapIdToPartitionO(id : Integer) : TimeEntity =
    this.entities.filter(entity => entity.id == id).head;

  // Mapping function from Integer value to entity PartitionNameRef value
  def mapIdToNameRef(id: Integer): String =
    this.entities.filter(entity => entity.id == id).head.identifier;

  // Transform a string to the same string with indentation
  def emit(string: String, indent: Int = 0): String = {
    // Match indentation settings
    indent match {
      case (-1) => this.level -= 1;
      case 1 => this.level += 1;
      case _ => {}
    }

    // Return indented string
    return " " * (this.INDENTATION_SPACE * this.level) + string;
  }

  class PartitionScheduleGeneratorException(message: String)
      extends Exception(message);
}
