$(document).ready(function(){
    interval();
});

var interval = function() {

    setTimeout(function() {

        $.ajax("act_status.php")
            .done(function(data) {
                //console.log(data);
                var obj = jQuery.parseJSON(data);
                processStatus(obj);
            })
            .fail(function(data) {
                console.log( "error",data );
            })
            .always(function() {
                //console.log( "complete" );
                interval();
            });

    }, 2000);
};

var processStatus =function(stat){
    if(stat.ActiveUsrName!==null){
        $( "#topStatusPanel" ).html(stat.ActiveUsrName);
    } else {
        $( "#topStatusPanel" ).html("Wait for sportsman...");
    }
    
    if(stat.CronoStartStatus==="0"){
        $('#topStatusPanel').css({'border': '2px solid #FF0000'});
    } else {
        $('#topStatusPanel').css({'border': '2px solid #43A047'});
    }
};
