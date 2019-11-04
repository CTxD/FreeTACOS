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
            val entities : List[TimeEntity] = this.createTimeEntities(this.partitions, this.schedules);

            // Create "schedulability" table

            // Check the table for overlapping periods

            return true;
        }

        def appendSchedule(identifier : String, duration : Integer, offset : Integer) = {
            new ScheduleTime(identifier, duration, offset) :: this.schedules;
        }

        def populatePartitionIdentifier(name : String) = this.namePlaceholder = name;
        def populatePartitionRemainder(period : Integer, duration : Integer) = {
            // Append new partition to the list of PartitionTime
            new PartitionTime(
                this.namePlaceholder,
                period,
                duration
            ) :: this.partitions;
        }

        def createTimeEntities(partitions : List[PartitionTime], schedules : List[ScheduleTime]) : List[TimeEntity] = {
            var entities : List[TimeEntity] = List();

            // Map partitions and schedules to TimeEntity instances
            for(part <- partitions){
                // Filter schedules to the matching partition
                val schedule = schedules.filter(sched => sched.identifier == part.identifier);
                
                // Check that a schedule was found
                if(schedule == Nil) throw new Exception(f"No matching schedule with identifier ${part.identifier}");

                // Append configuration to entities
                new TimeEntity(part.identifier, part.period, part.duration, schedule.head.offset) :: entities;
            }

            return entities;
        }
    }

    class TimeEntity(val identifier : String, val period : Integer, val duration : Integer, val offset : Integer) {}
    class PartitionTime (val identifier : String, val period : Integer, val duration : Integer) {}
    class ScheduleTime(val identifier : String, val duration : Integer, val offset : Integer) {}
}