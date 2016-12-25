#lang racket

; ----------------------------------------- ;
; Play-ground
(define a 416)
(println "hello world")
(println (/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5) ) ) ) ) 
            (* 3 (- 6 2) (- 2 7) ) ) )

(define (sq a)
  (* a a)
  )

(define (sqs a b)
  (+ (sq a) (sq b))
  )

; ----------------------------------------- ;
; Ex-1.3 
(define ( e13 a b c )
  (cond ( (and (< a b) (< a c) ) (sqs b c) )
        ( (and (< b a) (< b c) ) (sqs a c) )
        ( else (sqs a b) )
        )
  )

(println (e13 3 4 5) )

; ----------------------------------------- ;
; Chapter 1.1.7
(define (sqrt-iter guess x)
  (if (good-enough? guess x)
    guess 
    (sqrt-iter (improve guess x)
               x)))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2)) 

(define (good-enough? guess x)
  (< (abs (- (sq guess) x) ) 0.001) )

(define (sqr x)
  (sqrt-iter 1.0 x))

(println (sqr 9))
; ----------------------------------------- ;
