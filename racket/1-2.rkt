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
(fast-expt 4 11)

; ----------------------------------------- ;
; Ex1.16 fast-square
(define (fast-sq b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-sq b (/ n 2))))
        (else (* 2 (fast-sq b (- n 1))))))

(fast-sq 2 0)
(fast-sq 2 1)
(fast-sq 2 2)
(fast-sq 2 4)
(fast-sq 2 10)
(fast-sq 2 11)

; ----------------------------------------- ;
; Ex1.17 multiplication using addition, double and halve
(define (ex1.17 a b)
  (define (add x y) (+ x y))
  (define (double x) (+ x x))
  (define (halve x) (/ x 2))
  
  (cond ((= b 0) 0)
        ((even? b) (double (ex1.17 a (halve b))))
        (else (add a (ex1.17 a (- b 1))))))

(ex1.17 3 0)
(ex1.17 3 1)
(ex1.17 3 2)
(ex1.17 3 4)
(ex1.17 3 5)
(ex1.17 3 6)

; ----------------------------------------- ;
; Ex1.18 multiplication using addition, double and halve
(define (ex1.18 a b)
  (define (add x y) (+ x y))
  (define (double x) (+ x x))
  (define (halve x) (/ x 2))

  (define (iter acc a b) 
    (cond ((= b 0) acc)
          ((even? b) (iter acc (double a) (halve b)))
          (else (iter (add acc a) a (- b 1)))))
  (iter 0 a b))

(ex1.18 3 0)
(ex1.18 3 1)
(ex1.18 3 2)
(ex1.18 3 4)
(ex1.18 3 5)
(ex1.18 3 6)

; ----------------------------------------- ;
; Ex1.19 Fibonacci numbers in a logarithmic 
(define (fib n)
  (define (fib-iter a b p q count)
    (cond ((= count 0) b)
          ((even? count)
           (fib-iter a 
                     b
                     (+ (square p) (square q)) ; p' 
                     (+ (* 2 p q) (square q))  ; q' 
                     (/ count 2)))
          (else (fib-iter (+ (* b q) (* a q) (* a p))
                          (+ (* b p) (* a q))
                          p 
                          q
                          (- count 1)))))

  (fib-iter 1 0 0 1 n))

(fib 0)
(fib 1)
(fib 2)
(fib 3)
(fib 4)
(fib 5)
(fib 6)
(fib 7)
(fib 8)
(fib 9)
(fib 10)
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
