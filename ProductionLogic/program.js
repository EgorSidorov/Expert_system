//Кашель
 var v0 = false
//Насморк
 var v1 = true
//Температура
 var v2 = "низкая"
//Более5дней
 var v3 = true
//Вывих
 var v4 = false
//Кровотечение
 var v5 = true
//Перелом
 var v6 = false
//Глубокий кашель
 var v7 = true
//Флюрография
 var v8 = true
//Слепота
 var v9 = false
//end var
//Жар
 var v10 = (v2 == "высокая")
//Грипп
 var v11 = (v10 & (v1 | v0)) | v3
//ОРВИ
 var v12 = !v11
//Вирусное
 var v13 = v11 | v12
//Воспаление легких
 var v14 = (v2 == "средняя" | v2 == "низкая" | v2 == "высокая" ) & v3 & v8
//Травма
 var v15 = v4 | v5 | v6
//ВТравмпункт
 var v16 = v15 | v6
//Больница
 var v17 = v15 && v10
//end rule