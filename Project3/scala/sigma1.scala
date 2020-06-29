/* Sigma.scala
 *
 * Compute sum = 1 + 2 + ... + n
 */

object HelloWorld
{

    def myprint(n:int){
        var a = n+50
        println(a)
    }
  def main () {
    var i = 0
    for(i <- 0 to 10){
      myprint(i)
    }
  }
}