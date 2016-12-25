#lang racket

; ----------------------------------------- ;
; Play-ground
; (define a 416)
; (println "hello world")
; (println (/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5) ) ) ) ) 
;             (* 3 (- 6 2) (- 2 7) ) ) )

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

; (println (e13 3 4 5) )

; ----------------------------------------- ;
; Chapter 1.1.7 with improvement
(define (sqrt-iter guess last x)
  (if (good-enough? guess last)
    guess 
    (sqrt-iter (improve guess x) guess x)))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2)) 

(define (good-enough? guess last)
  (< (abs (- guess last) ) (* guess 0.001)) )

(define (sqr x)
  (sqrt-iter 1.0 x x))


(printf "Squre-root of 10000000: ~a\n" (sqr 10000000))
(printf "Squre-root of   0.0003: ~a\n" (sqr 0.0003))

; ----------------------------------------- ;
; Ex-1.8 
(define (cube-iter guess last x)
  (if (good-enough? guess last)
    guess 
    (cube-iter (cube-improve guess x) guess x)))

(define (cube-improve guess x)
  (/ (+ (/ x (sq guess)) (* 2 guess)) 3))

(define (cube-root x)
  (cube-iter 1.0 x x))

(printf " Cube-root of 10000000: ~a\n" (cube-root 10000000))
(printf " Cube-root of   0.0003: ~a\n" (cube-root 0.0003))
; ----------------------------------------- ;




; ----------------------------------------- ;
