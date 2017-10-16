#lang racket

; iterative 
(define (reverse list1)
  (define (help l1 l2)
    (if (null? l1)
      l2
      (help (cdr l1) (cons (car l1) l2))))
  (help list1 (list)))

(reverse (list 1 4 9 16 25))

; recursive
(define (r-rv list1)
  (if (null? list1)
    (list)
    (append (r-rv (cdr list1)) (list (car list1)))))

(r-rv (list 1 4 9 16 25))
