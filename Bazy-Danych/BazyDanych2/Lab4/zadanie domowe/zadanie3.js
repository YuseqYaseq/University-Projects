db.question.mapReduce(
    //map
    function() {
        if(this.value != null) {
            // Usuń znak dolara i przecinka z pola "value", skonwertuj na inta,
            // a następnie prześlij do funkcji reduce
            var newValue = parseInt(this.value.replace("$", "").replace(",", ""));
            emit(this.category, newValue);
        }
    },
    
    //reduce
    function(key, values) {
        //Zsumuj wszystkie wartości
        return Array.sum(values);
    },
    
    //query output
    {
        //Rezultat mapReduce będzie dostępny w kolekcji "results"
        out: "results"
    }    
)
// Wyświetl zawartość "results"
db.results.find({})