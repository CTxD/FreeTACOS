import scala.io.Source;
import scala.xml._;

object ScheduleGenerator{
  def main(args: Array[String]): Unit = {
    val configName : String = "configuration.xml";

    var lines = this.xmlLinesToList(configName);

    for(line <- lines){
      println(line);
    }
  }

  def xmlLinesToList(filename : String) : List[Node] = {
    XML.loadFile(filename).toList;
  }
}