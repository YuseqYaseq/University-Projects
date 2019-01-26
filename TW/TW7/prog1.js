
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

var Fork = function() {
    this.state = 0;
    return this;
}

Fork.prototype.acquire = function(delay, cb) { 
    // zaimplementuj funkcje acquire, tak by korzystala z algorytmu BEB
    // (http://pl.wikipedia.org/wiki/Binary_Exponential_Backoff), tzn:
    // 1. przed pierwsza proba podniesienia widelca Filozof odczekuje 1ms
    // 2. gdy proba jest nieudana, zwieksza czas oczekiwania dwukrotnie
    //    i ponawia probe itd.
    if(this.state == 0) {
        this.state = 1;
        cb();
    } else {
        console.log("czekanie... " + delay);
        var self = this;
        setTimeout(function() { self.acquire(delay * 2, cb); }, delay); 
    }
}

Fork.prototype.release = function() { 
    this.state = 0; 
}

var Philosopher = function(id, forks) {
    this.id = id;
    this.forks = forks;
    this.f1 = id % forks.length;
    this.f2 = (id+1) % forks.length;
    return this;
}

function dine(id, f1, f2, is3rdMethod) {
        forks[f1].acquire(2, () => {
            console.log(id + " philosopher takes fork " + f1);
            setTimeout(() => forks[f2].acquire(2, () => {
                        console.log(id + " philosopher is eating using " + f1 + " " + f2 + ".");
                        for(d = 0; d < 1000000; ++d);
                        forks[f1].release();
                        forks[f2].release();
                        if(is3rdMethod)peopleAtTheTable--;
                        console.log(id + " philosopher leaves.");
                    }, 1));
        });
}

Philosopher.prototype.startNaive = function(count) {
    //console.log(this.id + "test");
    var forks = this.forks,
        f1 = this.f1,
        f2 = this.f2,
        id = this.id;
    
    // zaimplementuj rozwiazanie naiwne
    // kazdy filozof powinien 'count' razy wykonywac cykl
    // podnoszenia widelcow -- jedzenia -- zwalniania widelcow
    for(i = 0; i < count; ++i) {
        setTimeout(() => dine(id, f1, f2, false), 1);       
    }
    
}

Philosopher.prototype.startAsym = function(count) {
    var forks = this.forks,
        f1 = this.f1,
        f2 = this.f2,
        id = this.id;

    //swap every other fork
    if(id % 2 == 1) {
        tmp = f1;
        f1 = f2;
        f2 = tmp;
    }
    for(i = 0; i < count; ++i) {
        setTimeout(() => dine(id, f1, f2, false), 1);       
    }
}

var peopleAtTheTable = 0;

function tryToDine(id, f1, f2) {
    if(peopleAtTheTable < N - 1) {
        peopleAtTheTable++;
        setTimeout(() => dine(id, f1, f2, true), 1);
    } else {
        setTimeout(() => tryToDine(id, f1, f2), 20);
    }
}
Philosopher.prototype.startConductor = function(count) {
    var forks = this.forks,
        f1 = this.f1,
        f2 = this.f2,
        id = this.id;
    
    
    for(i = 0; i < count; ++i) {
        tryToDine(id, f1, f2);      
    }
}


var N = 5;
var forks = [];
var philosophers = []
for (var i = 0; i < N; i++) {
    forks.push(new Fork());
}

for (var i = 0; i < N; i++) {
    philosophers.push(new Philosopher(i, forks));
}

for (var j = 0; j < N; j++) {
    //philosophers[j].startNaive(5);
    philosophers[j].startAsym(5);
    //philosophers[j].startConductor(5);
}






