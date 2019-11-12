import Validator.{Validator, ValidationException};
import ModuleGenerator.startGenerator;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter};
import scala.xml._;
import PartitionScheduleGenerator.{generateSchedule, PartitionScheduleGeneratorException};

object Main {
  var validator: Validator = new Validator();

  def main(args: Array[String]): Unit = {
    var configPrint = false;
    var configName = "";

    // Match input parameter attributes
    for (arg <- args; id <- 1 to args.length) arg match {
      case "-p" | "--print" => configPrint = true
      case "--filename" | "-f" => configName = args(id - 1);
      case _ => {}
    }

    try {
      println(Console.YELLOW + "Fetching xml file");
      var lines = this.xmlLinesToList(configName);

      println(Console.YELLOW + "Generating code");
      val generatedString = startGenerator(this.validator, lines);

      // validator will throw an exception if the check is unsuccessful
      println("Validating schedule configuration");

      val schedule = this.validator.checkScheduleValidity();
      println(Console.GREEN + "Validation succeeded")

      if (configPrint) {
        // Print the valid schedule if -p flag is passed
        println(Console.BLUE + "Valid Schedule configuration:");
        println(schedule._1);
      }

      // Start the schedule generator based on the valid schedule configuration
      var generatedSchedule : String = generateSchedule(schedule._2, validator.entities);

      println(Console.YELLOW + "Writing to file");
      val moduleWriter = new PrintWriter(new File("../src/kernel/arinc_module.cpp"));
      moduleWriter.write(generatedString);
      moduleWriter.close();

      println(Console.GREEN + "ArincModule successfully written");

      val scheduleWriter = new PrintWriter(new File("../src/kernel/core_schedule.cpp"));
      scheduleWriter.write(generatedSchedule);
      scheduleWriter.close();

      println("PartitionSchedule successfully written");

      println(Console.GREEN + "Success");
    } catch {
      // Handle exceptions, from the different modules - module_generator, partition_schedule_generator and validator
      case err: FileNotFoundException =>
        println(Console.RED + "You need to specify input file with --filename {filename} or -f {filename}");
      case err: PartitionScheduleGeneratorException =>
        println(Console.RED + f"PartitionScheduleGenerationError: ${err.getMessage()}");
      case err: ValidationException =>
          println(Console.RED + f"Validation error: ${err.getMessage()}");
      case err: NoClassDefFoundError =>
          println(Console.RED + f"Missing class: ${err.getMessage()}");
      case err: Exception =>
        println(Console.RED + f"Generation error: ${err.getMessage()}");
      case _: Throwable => {
        println(Console.RED + "Some unexpected error happened");
      }
    }
  }

  // Function for reading xml file
  def xmlLinesToList(filename: String): List[Node] = {
    return XML.loadFile(filename).toList;
  }
}
