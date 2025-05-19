:- dynamic symptom/1.

% Facts: Symptoms of diseases
disease(flu) :-
    symptom(fever),
    symptom(cough),
    symptom(body_ache).

disease(cold) :-
    symptom(cough),
    symptom(sneezing),
    symptom(runny_nose).

disease(allergy) :-
    symptom(sneezing),
    symptom(runny_nose),
    symptom(itchy_eyes).

disease(covid19) :-
    symptom(fever),
    symptom(cough),
    symptom(shortness_of_breath),
    symptom(loss_of_taste).

% Rules to check if patient has symptoms
has_symptom(S) :-
    symptom(S).

% Diagnosis rule: find disease matching given symptoms
diagnose(Disease) :-
    disease(Disease).

% To enter symptoms interactively
ask_symptoms :-
    write('Enter symptom (or "done" to finish): '), read(Symptom),
    ( Symptom = done -> true
    ; assert(symptom(Symptom)),
      ask_symptoms).

% Clear old symptoms (to allow multiple runs)
clear_symptoms :-
    retractall(symptom(_)).

% Main interaction loop
run_diagnosis :-
    clear_symptoms,
    write('Medical Diagnosis Expert System'), nl,
    write('Enter symptoms one by one, type done when finished.'), nl,
    ask_symptoms,
    ( diagnose(Disease) ->
        format('Possible diagnosis: ~w~n', [Disease])
    ; write('No diagnosis could be made with given symptoms.'), nl
    ).

/* 
Sample steps to run this program in SWI-Prolog:

1. Load this file:
   ?- consult('filename.pl').

2. Run the diagnosis:
   ?- run_diagnosis.

3. Enter symptoms one by one at the prompt, for example:
   Enter symptom (or "done" to finish): fever.
   Enter symptom (or "done" to finish): cough.
   Enter symptom (or "done" to finish): body_ache.
   Enter symptom (or "done" to finish): done.

4. The system will output:
   Possible diagnosis: flu

5. You can repeat with different symptoms to get other diagnoses.

Example inputs you can try:
- fever. cough. body_ache. done.
- cough. sneezing. runny_nose. done.
- sneezing. runny_nose. itchy_eyes. done.
- fever. cough. shortness_of_breath. loss_of_taste. done.
*/
