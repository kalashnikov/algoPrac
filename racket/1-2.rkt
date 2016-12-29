#lang racket

(define (square x)
  (* x x))

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
; Ex.1.12 Pascal's triangle
(define (ex1.12 n m )
  (if (or (= n m) (= m 0)) 
      1
      (+ (ex1.12 (- n 1) m) 
         (ex1.12 (- n 1) (- m 1)))))

(ex1.12 4 2)

; ----------------------------------------- ;
; 1.2.4 Exponentiation 
(define (fast-expt b n)
  
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))

(fast-expt 4 10)

; ----------------------------------------- ;
; 1.2.6 Testing for Primality - The Fermat test 
(define (fast-prime? n times) 
  (define (expmod base exp m)
    (cond ((= exp 0) 1)
          ((even? exp)
           (remainder (square (expmod base (/ exp 2) m))
                      m))
          (else
           (remainder (* base (expmod base (- exp 1) m))
                      m))))
           
  (define (fermat-test n)
    (define (try-it a)
      (= (expmod a n n) a))
    (try-it (+ 1 (random (- n 1)))))

  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))

(fast-prime? 90 5)

; ----------------------------------------- ;
