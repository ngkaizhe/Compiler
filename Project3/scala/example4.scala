/* for statement consideration*/
object HelloWorld {
   // variables
  var n: int = 8
  var Fn: int = 1
  var FNminus1: int = 1
  var temp: int
  var i = 0

  def main () {
    // compute the nth Fibonacci number
    for(i <- 2 to n) {
      temp = Fn
      Fn = Fn + FNminus1
      FNminus1 = temp
      i = i + 1
    }
    
    // print result
    print ("Result of computation: ")
    println (Fn)
  }
}