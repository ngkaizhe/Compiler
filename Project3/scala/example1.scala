/* if statement, double consideration */
object HelloWorld {
  var af = 1.5
  var bf: float
  def main () {
    // Print text to the console
    bf = 6.5
    af = af + bf - af * af / bf + 3.6
    print ("af value is -> ")
    println (af)
    print ("-af value is -> ")
    println (-af)

    if(af > 0.0){
        println("af is larger than zero!")
    }

    else
    {
        println("af is smaller than zero!")
    }
    
    if(-af > 0.0)
        println("-af is larger than zero!")
    else
        println("-af is smaller than zero!")

    println ("Hello World")
  }
}