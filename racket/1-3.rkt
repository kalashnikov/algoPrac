#lang racket

(define (average x y) (/ (+ x y) 2))
(define (square x) (* x x))
(define (cube x) (* x x x))

; ----------------------------------------- ;
; Higer-order procedure  
(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b))))

; Apply term to the range (a, b) 

; Integral
; Without lambda
; (define (integral f a b dx)
;   (define (add-dx x) (+ x dx))
;   (* (sum f (+ a (/ dx 2.0)) add-dx b)
;      dx))

; exact value is 1/4

; ----------------------------------------- ;
; 1.3.2 Lamda
(define (integral f a b dx)
  (define (add-dx x) (+ x dx))
  (* (sum 
       f 
       (+ a (/ dx 2.0)) 
       (lambda (x) (+ x dx)) 
       b)
     dx))

(integral cube 0 1 0.01)
(integral cube 0 1 0.001)

; ----------------------------------------- ;
; Normal
;
; (define (f x y)
;   (define (f-helper a b)
;     (+ (* x (square a ))
;        (* y b)
;        (* a b)))
;   (f-helper (+ 1 (* x y))
;             (- 1 y)))

; Lambda 
;
; (define (f x y)
;   (lambda ( a b)
;     (+ (* x (square a ))
;        (* y b)
;        (* a b)))
;   (+ 1 (* x y))
;   (- 1 y))

; Using 'let' 
(define (f x y)
  (let ((a (+ 1 (* x y)))
        (b (- 1 y)))
    (+ (* x (square a))
       (* y b)
       (* a b))))

; Alternative: Using 'define'
; 
; (define (f x y)
;   (define a (+ 1 (* x y)))
;   (define b (- 1 y))
;   (+ (* x (square a))
;      (* y b)
;      (* a b)))

; ----------------------------------------- ;
; 1.3.3 Procedures as General Methods 
; Finding roots of equations by the half-interval method

(define (search f neg-point pos-point)
  (define (close-enough? x y)
    (< (abs (- x y)) 0.001))
  (let ((midpoint (average neg-point pos-point)))
    (if (close-enough? neg-point pos-point)
      midpoint
      (let ((test-value (f midpoint)))
        (cond ((positive? test-value)
               (search f neg-point midpoint))
              ((negative? test-value)
               (search f midpoint pos-point))
              (else midpoint))))))

(define (half-interval-method f a b)
  (let ((a-value (f a))
        (b-value (f b)))
    (cond ((and (negative? a-value) (positive? b-value))
           (search f a b))
          ((and (negative? b-value) (positive? a-value))
           (search f b a))
          (else
            (error "Values are not of opposite sign" a b)))))

(half-interval-method sin 2.0 4.0)
(half-interval-method (lambda (x) (- (* x x x) (* 2 x) 3))
                      1.0
                      2.0)
; ----------------------------------------- ;
; Finding fixed points of functions 
(define tolerance 0.00001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2) 
    (< (abs (- v1 v2)) tolerance))

  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next 
        (try next))))
  (try first-guess))

(fixed-point cos 1.0)
(fixed-point (lambda (y) (+ (sin y) (cos y)))
             1.0)

; ----------------------------------------- ;
; 1.3.4 Procedures as Returned Values
(define (average-damp f)
  (lambda (x) (average x (f x))))

((average-damp square) 10)

(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y)))
               1.0))
(sqrt 1000)

(define (cube-root x) 
  (fixed-point (average-damp (lambda (y) (/ x (square y))))
               1.0))
(cube-root 1000)
; ----------------------------------------- ;
