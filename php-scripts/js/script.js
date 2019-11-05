function NewGame() {
    $.ajax({
        type: 'post',
        url: 'clear2.php',
        data: ('new_game'),
        success: progress(100, 100, $('#progressBar'))
    });
};

var updateInt = window.setInterval(refreshTable, 500);

function refreshTable() {
    //document.getElementById("txtHint").innerHTML = "Waiting for data from server..";
    xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("txtHint").innerHTML = this.responseText;
        }
        console.log(this.responseText);
    }
    xmlhttp.open("GET", "display.php", true);
    xmlhttp.send();
}

function progress(timeleft, timetotal, $element) {
    $('#newGameBtn').prop('disabled', true);
    $('#progressBar').prop('hidden', false);
    var progressBarWidth = timeleft * $element.width() / timetotal;
    $element.find('div').animate({ width: progressBarWidth }, 500).html(Math.floor(timeleft / 60) + ":" + timeleft % 60);
    if (timeleft > 0) {
        setTimeout(function() {
            progress(timeleft - 1, timetotal, $element);
        }, 1000);
    } else {
        $('#newGameBtn').prop('disabled', false);
        $('#progressBar').prop('hidden', false);
        window.alert("Tiden är slut!");
    }
};