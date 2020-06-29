object HelloWorld{
    var a = 5
    var c: int

    // function declaration
    def add(a:int, b:int): int
    {
        return a+b
    }

    // main statements
    def main(){
        c = add(a, 10)
        println("You should output -> -15, and loop till 10")

        if(c > 10) println(-c)
        else println(c)

        // for loop execution with a range
        for( a <- 1 to 10){
            print( "Value of a: ")
            println( a )
        }

        return
    }
}