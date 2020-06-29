object HelloWorld{
    val a = 5
    var c: int

    // function declaration
    def add(a:int, b:int): int
    {
        return a+b
    }

    // main statements
    def main(){
        c = add(a, 10)
        println("You should output -> -15")

        if(c > 10) println(-c)
        else println(c)

        return
    }
}