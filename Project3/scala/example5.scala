object HelloWorld{
    val a:float = 0.0
    var c: float

    // function declaration
    def add(a:float, b:float): float
    {
        return a+b
    }

    // main statements
    def main(){
        c = add(a, 10.0)

        if(c > 9.9) println(true)
        else println(false)

        if(9.8 < 9.9) println(true)
        else println(false)

        if(c >= 9.9) println(true)
        else println(false)

        if(9.8 <= 9.9) println(true)
        else println(false)

        if(10.0 == c) println(true)
        else println(false)

        if(9.8 != 9.9) println(true)
        else println(false)

        return
    }
}