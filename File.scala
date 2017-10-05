package memes.orderedfile


class OrderedFile {
	var root : Node
	var height : Int
	
	def densityMinima : Seq[Double] = (0 until height) map (0.5 - _/(4.0 * h))
	def densityMaxima : Seq[Double] = (0 until height) map (0.75 + _/(4.0 * h))

	def highestViolatedNode(leaf : Leaf) : Option[Node] = {
		val minima = densityMinima
		val maxima = densityMaxima
		var curNode : Node = leaf
		var violatedNode : Option[Node] = None
		
	}

	def insert(i: Int) : Unit = {
		val appropriateLeaf = findLeaf(root, i)
		put
		val minsDensity = 
	}

	def putInLeaf(leaf: Leaf, value: Int) : Unit = {
		var index : Int = 0
		for(i <- 0 until leaf.slots) {
			leaf.stuff(i) match {
				case Some(thing) => if(thing < value) index = i
				case _ => ()
			}
		}
		val next = nextHole(leaf, index)
		val prev = prevHole(leaf, index)
		if(prev < next) {
			for(i <- prev until index){
				leaf.stuff(i) = leaf.stuff(i+1)
			}
			leaf.stuff(index) = Some(value)
		}else{
			for(i <- index+1 to next){
				leaf.stuff(i+1) = leaf.stuff(i)
			}
			leaf.stuff(index+1) = Some(value)
		}
	}

	def nextHole(leaf: Leaf, index: Int) : Option[Int] = {
		var i : Int = index
		while(i < leaf.slots && leaf.stuff(i) != None) i++
		return i match {
			case leaf.slots => None
			case _ => Some(i)
		}
	}

	def prevHole(leaf: Leaf, index: Int) : Option[Int] = {
		var i : Int = index
		while(i >= 0 && leaf.stuff(i) != None) i--
		return i match {
			case -1 => None
			case _ => Some(i)
		}
	}

	def findLeaf(node: Node, value: Int) : Leaf = {
		return node match {
			case InteriorNode(left, right) => if(left.max > value) findLeaf(right, value) else findLeaf(left, value)
			case x : Leaf => x
		}
	}
}



sealed abstract class Node(parent: Option[Node]) {
	var size : Int
	var slots : Int
	var max : Int
	def density : Double = (Double)size/(Double)slots
	def changeSize(s : Int) : Unit = {
		size += s
		parent match {
			case Some(p) => p.increaseSize(s)
			case None => ()
		}
	}
}
case class InteriorNode(left: Node, right: Node, _parent: Option[Node]) extends Node(_parent) {

}
case class Leaf[T](stuff: Seq[Option[Int]], _parent: Option[Node], prev: Option[Leaf], next: Option[Leaf]) extends Node(_parent) {

}
