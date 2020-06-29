/* while,if stmt without bracket consideration, if(true) */
object HelloWorld {
  var af = 2
  var i = 1
  def main () {
    // Print text to the console
    while (i <= 10)
        i = i + 1
    
    println("i value should be 11")
    println("")
    
    if(true)
        print ("i value is -> ")
    
    if(true)
        println (i)
    else
        println ("Error")
  }
}