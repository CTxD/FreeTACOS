import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;

object ScheduleGenerator{
  def main(args: Array[String]): Unit = {
    val configName : String = "exampleschedule.xml";

    try{
      val lines = this.xmlLinesToList(configName);

      for(line <- lines){
        println(line.toString());
      }
    } catch {
      case err : NoClassDefFoundError => {
        println("Class Not Found Exception");
      }
      case err : FileNotFoundException => {
        println("Input file not found");
      }
    }
  }

  def xmlLinesToList(filename : String) : List[Node] = {
    return XML.loadFile(filename).toList;
  }
}