#lang racket

; ----------------------------------------- ;
; Exercise: Counting change
; [Chanllege] Better algorithm
(define (count-change amount)
  (cc amount 5 ))

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (= kinds-of-coins 0)) 0)
        (else (+ (cc amount 
                     (- kinds-of-coins 1))
                 (cc (- amount 
                        (first-denomination kinds-of-coins))
                     kinds-of-coins)))))

(define (first-denomination kinds-of-coins)
  (cond ((= kinds-of-coins 1) 1)
        ((= kinds-of-coins 2) 5)
        ((= kinds-of-coins 3) 10)
        ((= kinds-of-coins 4) 25)
        ((= kinds-of-coins 5) 50)))

(count-change 100)

; ----------------------------------------- ;
; Ex 1.11 
(define (ex1.11_recursive n)
  (if (< n 3) 
       n
       (+ (ex1.11_recursive (- n 1))
                 (* 2 (ex1.11_recursive (- n 2)))
                 (* 3 (ex1.11_recursive (- n 3))))))
(ex1.11_recursive 10)

(define (ex1.11_iterative n)
  (define (helper n1 n2 n3 count)
    (if (= count 0) 
      n1
      (helper (+ n1 (* 2 n2) (* 3 n3)) n1 n2 (- count 1))))

  (if (< n 3)
    n 
    (helper 2 1 0 (- n 2)))) 

(ex1.11_iterative 10)

; ----------------------------------------- ;


