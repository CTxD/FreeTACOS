// Validator object for validating the schedules configuration in terms of offset, period and duration
object Validator {
    class Validator {
        var partitions : List[PartitionTime] = List();
        var schedules : List[ScheduleTime] = List();
        
        // Placeholder object for building partitions
        var namePlaceholder : String = "";

        def checkScheduleValidity() : Boolean = {
            // Check that there are as many schedule configurations as partition configurations
            if(!(this.partitions.length == this.schedules.length)) return false;

            // Create a list of time entities
            val entities : List[TimeEntity] = this.createTimeEntities();

            // Create "schedulability" table
            println("Creating table");
            this.createTable(entities);

            // Check the table for overlapping periods

            return true;
        }
        
        // Done using inspiration from this lecture: https://www.moodle.aau.dk/pluginfile.php/1163980/mod_resource/content/10/Lecture-4.pdf
        def createTable(entities : List[TimeEntity]){
            println("Creating table - " + entities.length);
            for(ent <- entities){
                println("Got this far :)");
            }
        }

        def appendSchedule(identifier : String, duration : Integer, offset : Integer) = {
            this.schedules = new ScheduleTime(identifier, duration, offset) :: this.schedules;
        }

        def populatePartitionIdentifier(name : String) = this.namePlaceholder = name;
        def populatePartitionRemainder(period : Integer, duration : Integer) = {
            // Append new partition to the list of PartitionTime
            this.partitions = new PartitionTime(
                this.namePlaceholder,
                period,
                duration
            ) :: this.partitions;
        }

        def createTimeEntities() : List[TimeEntity] = {
            var entities : List[TimeEntity] = List();

            // Map partitions and schedules to TimeEntity instances
            for(part <- this.partitions){
                // Filter schedules to the matching partition (Trim down the result)
                val sched = this.schedules.filter(elem => elem.identifier.trim() == part.identifier.trim());

                // Check that a schedule was found
                if(sched.length < 1) throw new Exception(f"No matching schedule with identifier ${part.identifier}");

                // Append configuration to entities
                entities = new TimeEntity(part.identifier, part.period, part.duration, sched.head.offset) :: entities;
            }

            return entities;
        }
    }

    

    class TimeEntity(val identifier : String, val period : Integer, val duration : Integer, val offset : Integer) {}
    class PartitionTime (val identifier : String, val period : Integer, val duration : Integer) {}
    class ScheduleTime(val identifier : String, val duration : Integer, val offset : Integer) {}
}