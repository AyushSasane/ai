symptom(fever).
symptom(cough).
symptom(sore_throat).
symptom(headache).


disease(flu) :-
    symptom(fever),
    symptom(cough),
    symptom(headache),
    symptom(sore_throat).

disease(covid19) :-
    symptom(fever),
    symptom(cough),
    symptom(shortness_of_breath),
    symptom(loss_of_taste_smell).

disease(common_cold) :-
    symptom(sneezing),
    symptom(cough),
    symptom(sore_throat).


diagnose :-
    disease(D),
    write('Diagnosis: You may have '), write(D), nl,
    explanation(D), !.

diagnose :-
    write('No diagnosis could be determined. Please consult a doctor.'), nl.


explanation(flu) :-
    write('Explanation: Detected fever, cough, headache, and sore throat.'), nl.
explanation(covid19) :-
    write('Explanation: Detected fever, cough, shortness of breath, and loss of taste/smell.'), nl.
explanation(common_cold) :-
    write('Explanation: Detected sneezing, cough, and sore throat.'), nl.


:- initialization(diagnose).