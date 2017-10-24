#lang racket

(define (for-each op items)
  (cond ((null? items) null)
        ((integer? items) (op items)) 
        (else (op (car items)) 
              (for-each op (cdr items))))) 

; Better solution 
; http://community.schemewiki.org/?sicp-ex-2.23
(define (for-each op items)
  (cond ((not (null? items))
         (op (car items))
         (for-each op (cdr items)))))

(for-each (lambda (x) (newline) (display x))
          (list 57 321 88))

