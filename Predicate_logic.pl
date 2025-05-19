Predicate logic
% --- FACTS ---
parent(john, alice).
parent(john, bob).
parent(mary, alice).
parent(mary, bob).
parent(bob, tom).

male(john).
male(bob).
male(tom).

female(mary).
female(alice).

% --- RULES ---
father(X, Y) :-
    parent(X, Y),
    male(X).

mother(X, Y) :-
    parent(X, Y),
    female(X).

grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

% --- OUTPUT ---
run :-
    write('Father of Alice: '), father(F, alice), write(F), nl,
    write('Mother of Bob: '), mother(M, bob), write(M), nl,
    write('Grandparent of Tom: '), grandparent(GP, tom), write(GP), nl,
    write('Siblings of Alice: '), sibling(alice, S), write(S), nl.

% --- AUTO EXECUTE ---
:- initialization(run).