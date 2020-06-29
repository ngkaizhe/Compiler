
/* fib.scala
 *
 * This test program computes the Nth Fibonacci number
 */

object HelloWorld
{
  // variables
  var n: int = 8
  var Fn: int = 1
  var FNminus1: int = 1
  var temp: int

  def main () {
    // compute the nth Fibonacci number
    while (n > 2) {
      temp = Fn
      Fn = Fn + FNminus1
      FNminus1 = temp
      n = n - 1
    }
    
    println("The result must be 21")
    println("")

    // print result
    print ("Result of computation: ")
    println (Fn)
  }
}