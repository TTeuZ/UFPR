let xhttp = new XMLHttpRequest();

xhttp.open("GET", "../data/students.json", true);
xhttp.send();

xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        console.log("Bataat")
    }
};