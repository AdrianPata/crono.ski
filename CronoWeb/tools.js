$(document).ready(function(){
    interval();
    
    $( "#btnShutDown" ).click(function() {
        var r = confirm("Shut down GSM module?");
        if (r === true) {
            $.ajax("act_shutdown.php")
            .done(function(data) {
                //console.log(data);
                //var obj = jQuery.parseJSON(data);
                //processStatus(obj);
                alert("Shut down: "+data);
            })
            .fail(function(data) {
                console.log( "error",data );
            })
            .always(function() {
                //console.log( "complete" );
            });
        }
    });
});

var statusVersion=0;



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
        var s="";
        
        if(stat.ActiveUsrStatus==="1") s="at start";
        if(stat.ActiveUsrStatus==="2") s="on track";
        if(stat.ActiveUsrStatus==="3") {
            var t=parseInt(stat.ResultStatus);
            t=t/(16000000/4/8);
            t=t.toFixed(3);
            s=t+" seconds";
        }
        $( "#topStatusPanel" ).html(stat.ActiveUsrName+" : "+s);
    } else {
        $( "#topStatusPanel" ).html("Wait for sportsman...");
    }
    
    //Load table data if it is necessary
    if(stat.Version!==null && statusVersion!==parseInt(stat.Version)){
        statusVersion=parseInt(stat.Version);
        loadTableData();
    }
    
    if(stat.CronoStartStatus==="0"){
        $( "#topStatusPanel" ).html("Wait for CronoStart...");
        $('#topStatusPanel').css({'border': '2px solid #FF0000'});
    } else {
        $('#topStatusPanel').css({'border': '2px solid #43A047'});
    }
};

var loadTableData=function(){
    $.ajax("act_results.php")
            .done(function(data) {
                //console.log(data);
                var obj = jQuery.parseJSON(data);
                displayTableData(obj);
            })
            .fail(function(data) {
                console.log( "error",data );
            })
            .always(function() {
                //console.log( "complete" );
            });
};

var displayTableData=function(table){
    $( ".tblRow" ).remove();
    row=1;
    if(table.total!==0){
        for(i=0;i<table.total;i++){
            res=table.list[i];
            //console.log(i+":"+res.name);
            
            //Manage displayed row colors
            if(row===2){
                rowClass="tblRow tblRowCol2";
                row=1;
            } else {
                rowClass="tblRow tblRowCol1";
                row=2;
            }
            if(res.rid===table.max) rowClass="tblRow tblRowColSel";

            var t=parseInt(res.result);
            t=t/(16000000/4/8);
            t=t.toFixed(3);
            s=t+" sec";
            
            $('.maintable').append('<tr class="'+rowClass+'"><td>'+(i+1)+'</td><td>'+res.rid+'</td><td>'+res.name+'</td><td>'+s+'</td><td>'+res.rtime+'</td></tr>');
        }
    }
};