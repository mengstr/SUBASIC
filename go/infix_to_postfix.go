package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
	"unicode"
)

// Stack is a simple stack implementation
type Stack struct {
	items []string
}

// Push adds an item to the stack
func (s *Stack) Push(item string) {
	s.items = append(s.items, item)
}

// Pop removes and returns the top item from the stack
func (s *Stack) Pop() string {
	if len(s.items) == 0 {
		return ""
	}
	item := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return item
}

// Peek returns the top item from the stack without removing it
func (s *Stack) Peek() string {
	if len(s.items) == 0 {
		return ""
	}
	return s.items[len(s.items)-1]
}

// IsEmpty checks if the stack is empty
func (s *Stack) IsEmpty() bool {
	return len(s.items) == 0
}

// precedence returns the precedence of the operators
func precedence(op string) int {
	switch op {
	case "+", "-":
		return 1
	case "*", "/":
		return 2
	case "ABS":
		return 3
	default:
		return 0
	}
}

// isFunction checks if the token is a function
func isFunction(token string) bool {
	return token == "ABS"
}

// infixToPostfix converts an infix expression to a postfix expression
func infixToPostfix(expression string) []string {
	var output []string
	operatorStack := Stack{}
	token := ""

	for i := 0; i < len(expression); i++ {
		char := rune(expression[i])
		if unicode.IsDigit(char) {
			token += string(char)
			if i == len(expression)-1 || !unicode.IsDigit(rune(expression[i+1])) {
				output = append(output, token)
				token = ""
			}
		} else if unicode.IsLetter(char) {
			token += string(char)
			if i == len(expression)-1 || !unicode.IsLetter(rune(expression[i+1])) {
				if isFunction(token) {
					operatorStack.Push(token)
				} else {
					fmt.Printf("Unknown function: %s\n", token)
				}
				token = ""
			}
		} else if char == '(' {
			if token != "" {
				operatorStack.Push(token)
				token = ""
			}
			operatorStack.Push(string(char))
		} else if char == ')' {
			for !operatorStack.IsEmpty() && operatorStack.Peek() != "(" {
				output = append(output, operatorStack.Pop())
			}
			operatorStack.Pop() // remove '('
			if !operatorStack.IsEmpty() && isFunction(operatorStack.Peek()) {
				output = append(output, operatorStack.Pop())
			}
		} else if strings.ContainsRune("+-*/", char) {
			if token != "" {
				output = append(output, token)
				token = ""
			}
			for !operatorStack.IsEmpty() && precedence(operatorStack.Peek()) >= precedence(string(char)) {
				output = append(output, operatorStack.Pop())
			}
			operatorStack.Push(string(char))
		}
	}

	if token != "" {
		output = append(output, token)
	}

	for !operatorStack.IsEmpty() {
		output = append(output, operatorStack.Pop())
	}

	return output
}

// evaluatePostfix evaluates a postfix expression
func evaluatePostfix(postfix []string) int {
	evalStack := Stack{}

	for _, token := range postfix {
		if unicode.IsDigit(rune(token[0])) {
			evalStack.Push(token)
		} else if isFunction(token) {
			operand, _ := strconv.Atoi(evalStack.Pop())
			var result int
			switch token {
			case "ABS":
				result = int(math.Abs(float64(operand)))
			}
			evalStack.Push(strconv.Itoa(result))
		} else {
			rightOperand, _ := strconv.Atoi(evalStack.Pop())
			leftOperand, _ := strconv.Atoi(evalStack.Pop())
			var result int
			switch token {
			case "+":
				result = leftOperand + rightOperand
			case "-":
				result = leftOperand - rightOperand
			case "*":
				result = leftOperand * rightOperand
			case "/":
				result = leftOperand / rightOperand
			}
			evalStack.Push(strconv.Itoa(result))
		}
	}

	finalResult, _ := strconv.Atoi(evalStack.Pop())
	return finalResult
}

func xmain() {
	expression := "3*(1+1)-ABS(5-17)*12"
	expression = "2*ABS 1"
	postfix := infixToPostfix(expression)
	fmt.Println("Postfix Expression:", strings.Join(postfix, " "))
	result := evaluatePostfix(postfix)
	fmt.Println("Final Evaluation Result:", result)
}
