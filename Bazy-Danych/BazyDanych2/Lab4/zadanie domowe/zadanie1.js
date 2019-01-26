db.getCollection('question')
    .find({"category": "ORGANIZATIONS", "value":"$1000"})
    .sort({"show_number":1})