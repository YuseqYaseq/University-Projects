package twtutorial

import scala.concurrent._
import scala.concurrent.duration._
import ExecutionContext.Implicits.global
import scala.util.{Success, Failure}
import scala.util.Random

object Futures3 extends App {

  def asyncPrint(n: Int): Future[Int] = Future {
    blocking { Thread.sleep(Random.nextInt(500)) }
    println(n)
    n
  }

  def f1 = asyncPrint(1)
  def f2 = asyncPrint(2)
  def f3 = asyncPrint(3)

  // Exercise: ensure that 1,2,3 are written in order using combinators (see Futures4 and Futures5.scala)
  val x = for {
    r1 <- f1
    r2 <- f2
    r3 <- f3
  } yield()
  
  Thread.sleep(2000)
}
