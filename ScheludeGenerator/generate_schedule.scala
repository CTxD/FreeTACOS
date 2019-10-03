import scala.io.Source;
import scala.xml._;
import java.io.FileNotFoundException;
import java.io.{File, PrintWriter}

object ScheduleGenerator{
  def main(args: Array[String]): Unit = {
    val configName : String = "exampleschedule.xml";

    try{
      val lines = this.xmlLinesToList(configName);
      println(generate(lines))
      val writer = new PrintWriter(new File("gen.cpp" ))
      writer.write("Hello Scala")
      writer.close()
    } catch {
      case err : NoClassDefFoundError => {
        println("Class Not Found Exception");
      }
      case err : FileNotFoundException => {
        println("Input file not found");
      }

    }
  }

  def generate (lines: List[Any]): String = lines match {
    case Nil => ""
    case x::xs => x + generate(xs)
  }

  def xmlLinesToList(filename : String) : List[Node] = {
    return XML.loadFile(filename).toList;
  }
}