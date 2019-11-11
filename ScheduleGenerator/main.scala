import Validator.{Validator, ValidationException};
import ScheduleGenerator.startGenerator;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter};
import scala.xml._;

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
        // Print schedule here
        println(Console.BLUE + "Valid Schedule configuration:");
        println(schedule);
      }

      println(Console.YELLOW + "Writing to file");
      val writer = new PrintWriter(new File("../src/kernel/config.cpp"));
      writer.write(generatedString);
      writer.close();

      println(Console.GREEN + "Success");
    } catch {
      case err: NoClassDefFoundError => {
        println(Console.RED + "Class Not Found Exception");
      }
      case err: FileNotFoundException => {
        println(
          Console.RED + "You need to specify input file with --filename {filename} or -f {filename}");
      }
      case err: Exception => {
        println(f"Generation error: ${err.getMessage()}");
      }
      case err: ValidationException => {
        println(Console.RED + f"Validation error: ${err.getMessage()}");
      }
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
