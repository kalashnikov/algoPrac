#lang racket

; iter
(define (same-parity . items)
  (define check? 
    (if (odd? (car items))
      odd?
      even?))
  (define (helper ans items)
    (cond ((null? items) (reverse ans))
          ((check? (car items))
           (helper (cons (car items) ans) (cdr items)))
          (else 
            (helper ans (cdr items)))))
  (helper (list (car items)) (cdr items)))

; recur  => TODO 
; (define (same-parity-recur x . y)
;   (define check?
;     (if (odd? x)
;       odd?
;       even?))
;   (let ((first (car y)))
;     (cond ((null? y) '())
;           ((check? first)
;            (cons first (same-parity-recur (cdr y))))
;           (else 
;             (same-parity-recur (cdr y))))))

(same-parity 1 2 3 4 5 6 7)
(same-parity 2 3 4 5 6 7)
