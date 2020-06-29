/* while, if stmt, logical, remainder consideration */
object HelloWorld {
  var af = 2
  var i = 1
  def main () {
    // Print text to the console
    while (i <= 10){
        if(i % 2 == 1 && i % 3 == 0)
            println(i)
        else{
            println("skrt")
        } 
        i = i + 1
    }

    println ("Hello World")
  }
}