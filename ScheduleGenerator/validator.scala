// Validator object for validating the schedules configuration in terms of offset, period and duration
object Validator {
    class Validator {
        var partitions : List[PartitionTime] = List();
        var schedules : List[ScheduleTime] = List();

        // Placeholder object for building partitions
        var namePlaceholder : String = "";
        var affinityPlaceholder : Integer = 0;

        val TABLE_HEIGHT : Integer = 5;
        val TOTAL_CORES : Integer = 4;

        def checkScheduleValidity() : String = {
            // Check that there are as many schedule configurations as partition configurations
            if(!(this.partitions.length == this.schedules.length)) throw new ValidationException("The number of partitions does not match the number of partitions");

            // Create a list of time entities
            var entities : List[TimeEntity] = this.createTimeEntities();

            // Create "schedulability" table and check for overlapping schedules - return the configuration
            return this.createTable(entities);
        }

        // Done using inspiration from this lecture: https://www.moodle.aau.dk/pluginfile.php/1163980/mod_resource/content/10/Lecture-4.pdf (Overlapping activity schedule problem)
        def createTable(entities : List[TimeEntity]) : String = {
            // Initialise matrix of the matrix configuration and core list table (allocate space for all possible schedules)
            // This initialises a table of Affinity[Entities[Values]]
            var scheduleTable : Array[Array[Array[Integer]]] = Array(Array.ofDim[Integer](entities.length, this.TABLE_HEIGHT), Array.ofDim[Integer](entities.length, this.TABLE_HEIGHT), Array.ofDim[Integer](entities.length, this.TABLE_HEIGHT), Array.ofDim[Integer](entities.length, this.TABLE_HEIGHT));

            // Sort entities list based on when periods start (Default ascending based on offsets)
            var sortedEntities = entities.sortBy(ent => ent.offset);

            // Iterate through the entity table
            for(ent <- sortedEntities) {
                // Check for overlapping periods
                scheduleTable = this.generateAndCheckSchedule(ent, scheduleTable);
            }

            return printScheduleConfigation(entities, scheduleTable);
        }

        def printScheduleConfigation(entities : List[TimeEntity], scheduleTable : Array[Array[Array[Integer]]]) : String = {
          var emptyField = false;
          var cString = "|";
          for(c <- 0 to this.TOTAL_CORES - 1){
            cString = cString + f"---------------------------------------------------------------------|\n";
            cString = cString + f"|·············|·············|·····${c}·······|·············|·············|\n";
            cString = cString + f"| identifier  |   period    |  duration   |    offset   |  affinity   |\n";
            cString = cString + f"|---------------------------------------------------------------------|\n|";
            for(i <- 0 to entities.length - 1){
              for(j <- 0 to this.TABLE_HEIGHT - 1){
                if(scheduleTable(c)(i)(j) != null){
                  cString = cString + f"${this.mkRow(scheduleTable(c)(i)(j), 13)}|";
                }else{
                  emptyField = true;
                }
              }

              if(emptyField){
                cString = cString + f"             |             |             |             |             |\n|";
                emptyField = false;
              }else{
                cString = cString + "\n|";
              }
            }
          }
          cString = cString + f"---------------------------------------------------------------------|\n";

          return cString;
        }

        def mkRow(ins : Integer, space : Integer) : String = {
          val len = ins.toString().length();
          val whites = space - len;

          var rString = "";
          if((whites % 2) == 0){
            // Even number
            val whiteSpace = whites / 2;
            rString = " ".repeat(whiteSpace) + ins.toString() + " ".repeat(whiteSpace);
          }else{
            // Odd number
            val whiteSpace = math.floor(whites / 2).toInt;
            rString = " ".repeat(whiteSpace) + ins.toString() + " ".repeat(whiteSpace + 1);
          }

          return rString;
        }

        // Iterate through all schedules in the table and check the validity
        def checkScheduleOverlap(entity : TimeEntity, table : Array[Array[Integer]])
          : (Array[Array[Integer]], Boolean) = {
          // Get the total size of the table
          var entryCount = 0;
          for(entry <- 0 to table.size - 1) {
            // Check if the value is valid -> thereby there is an instance
            if(table(entry)(0) != null){
                entryCount = entryCount + 1;
            }
          }

          // Check if any entries has been assigned
          if(entryCount > 0){
            // Iterate through all entities in the table
            for(i <- 0 to entryCount) {
              val tperiod = table(i)(1);
              val toffset = table(i)(3);

              val tstart = tperiod + toffset;

              // If the starting point of the entititty ;) is lesser than the last finished one
              if(tstart >= entity.offset) {
                // Return false
                return (table, false);
              }
            }
          }

          var tableCopy = table;

          // Update the table entry
          tableCopy(entryCount)(0) = entity.id; // Set the id
          tableCopy(entryCount)(1) = entity.period; // Period
          tableCopy(entryCount)(2) = entity.duration; // Duration
          tableCopy(entryCount)(3) = entity.offset; // Offset
          tableCopy(entryCount)(4) = entity.affinity; // Affinity

          // All is good
          return (tableCopy, true);
        }

        // Iterate through all cores (based on affinity) to find the next core match
        def checkCoreOverlap(ent : TimeEntity, coreRemainder : Integer, doneRemainder : Integer, table : Array[Array[Array[Integer]]])
          : Array[Array[Array[Integer]]] = coreRemainder match {
            // If the partition has been assigned to all of it's number of cores (Affinity)
            case x if doneRemainder == -1 => {
              return table;
            }

            // If the affinity is valid (Bigger than 0 (1 core) and smaller than 4 (3 = 4 cores))
            // We always check the table from 0 -> total affinity (partition affinity)
            case x if (x >= 0 && x < 4) => {
              // Generate the new table and check
              val innerTable = this.checkScheduleOverlap(ent, table(coreRemainder));

              // Iterate over proceeding cores
              innerTable._2 match {
                case true => {
                    // Update the current table to the most recent
                    var tableCopy = table;
                    tableCopy(coreRemainder) = innerTable._1;

                    this.checkCoreOverlap(ent, coreRemainder - 1, doneRemainder - 1, tableCopy);
                }
                case false => this.checkCoreOverlap(ent, coreRemainder - 1, doneRemainder, table);
              }
            }

            // If the partition can not be scheduled on any cores
            case x if x == -1 && doneRemainder != -1 => throw new ValidationException(f"The schedule conflicts on ${ent.identifier}");

            // If an invalid affinity is entered
            case _ => throw new ValidationException(f"The partition ${ent.identifier} has an invalid affinity of ${ent.affinity}");
        }

        def generateAndCheckSchedule(entity : TimeEntity, table : Array[Array[Array[Integer]]])
          : Array[Array[Array[Integer]]] = this.checkCoreOverlap(entity, this.TOTAL_CORES - 1, entity.affinity, table);


        def appendSchedule(identifier : String, duration : Integer, offset : Integer) = {
            this.schedules = new ScheduleTime(identifier, duration, offset) :: this.schedules;
        }

        def populatePartitionIdentifier(name : String, affinity : Integer) = {
            this.namePlaceholder = name;
            this.affinityPlaceholder = affinity;
        }

        def populatePartitionRemainder(period : Integer, duration : Integer) = {
            // Append new partition to the list of PartitionTime
            this.partitions = new PartitionTime(
                this.namePlaceholder,
                period,
                duration,
                this.affinityPlaceholder
            ) :: this.partitions;
        }

        def createTimeEntities() : List[TimeEntity] = {
            var entities : List[TimeEntity] = List();

            // Map partitions and schedules to TimeEntity instances
            for(id <- 1 to this.partitions.length){
                val part = this.partitions(id - 1);
                // Filter schedules to the matching partition (Trim down the result)
                val sched = this.schedules.filter(elem => elem.identifier.trim() == part.identifier.trim());

                // Check that a schedule was found
                if(sched.length < 1) throw new ValidationException(f"No matching schedule with identifier ${part.identifier}");

                // Append configuration to entities
                entities = new TimeEntity(id, part.identifier, part.period, part.duration, sched.head.offset, part.affinity) :: entities;
            }

            return entities;
        }
    }

    // Classes for storing the schedule data in objects are defined
    class TimeEntity(val id : Integer, val identifier : String, val period : Integer, val duration : Integer, val offset : Integer, val affinity : Integer) {}
    class PartitionTime (val identifier : String, val period : Integer, val duration : Integer, val affinity : Integer) {}
    class ScheduleTime(val identifier : String, val duration : Integer, val offset : Integer) {}

    class ValidationException(message : String) extends Exception(message);
}
