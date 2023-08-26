let Alldata=[];
let flameData=[];
let gazData=[];
let xValues =[];
//setInterval(() => {
 //    location.reload();
  // }, 5000);


  
activeButtons=(active)=>{
  const desctiveButton = $('#desctive')[0]
  const activeButton = $('#active')[0]
  const restartButton = $('#restart')[0]
  const configLink = $('#configLink')[0]
  if(active){
    //Activate the buttons

    desctiveButton.removeAttribute('disabled');
    activeButton.removeAttribute('disabled');
    restartButton.removeAttribute('disabled');
    configLink.classList.remove("hidden");
    
  }else{
    //Disable the buttons
    desctiveButton.setAttribute('disabled', '');
    activeButton.setAttribute('disabled', '');
    restartButton.setAttribute('disabled', '');
    configLink.classList.add("hidden");
  }
}

toggleStatus=(statu)=>{
  
  const desctiveButton = $('#desctive')[0]
  const activeButton = $('#active')[0]
  
  
  if(statu=="On"){
    $('#alertStatus')[0].innerHTML="Alert status : On";
    activeButton.setAttribute('disabled', '');
    if($('#connected')[0].innerHTML=="Connected 🟢")
    desctiveButton.removeAttribute('disabled');
  }else{
    $('#alertStatus')[0].innerHTML="Alert status : Off";
    desctiveButton.setAttribute('disabled', '');
    if($('#connected')[0].innerHTML=="Connected 🟢")
      activeButton.removeAttribute('disabled');
  }
}

pingArduino=()=>{
      /* ************************ */
      /* ********* PING ********* */
      const ip = $("#ip").val();
      axios
      .get("http://" + ip + ":80/message", {
        params: {
          msg: "ping",
        },
      })
      .then((res) => {
        statusCode = res.status;
        if (statusCode === 200) {
          $('#connected')[0].innerHTML="Connected 🟢";
          activeButtons(true)
        }else{
          $('#connected')[0].innerHTML="Not Connected 🔴";
          activeButtons(false)
          
        }
        console.log(res)
      })
      
      .catch((err)=>{
        $('#connected')[0].innerHTML="Not Connected 🔴";
        activeButtons(false)
        console.log(err)
        console.log("err")
        
      });
}

 $(document).ready( 
  
  
  setTimeout(function(){
    activeButtons(false)
     axios.get('tools/show.php',{
          headers: {
            'Content-Type': 'application/json'
          }
        })
       .then(function (response) {
         Alldata = response.data;
         Alldata.map((e)=>{
          flameData.push(e.FlameValue);
          gazData.push(e.GazValue);
          xValues.push(e.Date.split(" ")[1]);
         
     })
         
       })
       .catch(function (error) {
         console.log(error);
       });
      //  document.getElementById('myChart').style="width:100%;max-width:600px"
     



       if($("#statu").val()=="On"){
        toggleStatus("On")
       }


      pingArduino()




   }),500);


setTimeout(async()=>{
   const ctx = document.getElementById('myChart').getContext('2d');
   
 


  var flameDataReversed=flameData.reverse();
  
  flameDataReversed.forEach((element, index) => {
    flameDataReversed[index] = -element + 330;
  });


  var gazDataReversed=gazData.reverse();
  console.log(gazDataReversed);

  gazDataReversed.forEach((element, index) => {
    gazDataReversed[index] = element -658;
  });
  console.log(gazDataReversed);

  
  const chart = new Chart(ctx, {
     type: 'line',
     data: {
       labels: xValues.reverse(),
       datasets: [{
         label: 'Gas Value',
         data: gazDataReversed,
         borderColor: "red",
         backgroundColor: "rgba(255, 0, 0,0.2)",
         borderWidth: 1,
         pointBorderWidth:1,
         fill: false 
       }, {
         label: 'Flame',
         data: flameDataReversed,
          borderColor: "blue",
          backgroundColor: "rgba(0, 0, 235, 0.3)",
          borderWidth: 1,
          fill: false
          }, {
       }]
     },
     options: {
          animation: false,
          scales: {
               x: {
                 type: 'time',
                 time: {
                    unit: 'second',
                    displayFormats: {
                        second: 'mm:ss'
                    },
                    stepSize: 1
                 },
                 title: {
                   display: true,
                   text: 'Date'
                 }
               },
               yAxes: [
                    {
                      ticks: {
                        beginAtZero: true, // Start the scale at 0
                    //     stepSize: 10, // Set the scale step size to 10
                    //     max: 1000, // Set the maximum value of the scale to 100
                      },
                    },
                  ],
       }
     }
   });
},500)

   $("#desctive").click(function(){

     // this.prop('disabled', true);
     // $('#active').prop('disabled', false);

     let formData=new FormData();
        formData.append('msg','Off');
        const ip =$("#ip").val()
        Alert.warning('Turning OFF the alert system...','Warning',{displayDuration: 3000})
      axios({
        url:"http://"+ip+":80/message",
        method: "POST",
        data: formData,
      })
        .then((res) => {console.log(res)})
        
        .catch((err)=>console.log(err));
   });
   $("#active").click(function(){

     // this.prop('disabled', true);
     // $('#desctive').prop('disabled', false);

     let formData=new FormData();
        formData.append('msg','On');
        const ip =$("#ip").val()
        Alert.warning('Turning ON the alert system...','',{displayDuration: 3000})
     axios({
          url:"http://"+ip+":80/message",
          method: "POST",
          data: formData,
        })
          .then((res) => {console.log(res)})
          .catch((err)=>console.log(err));
   }
   );
   
   $("#restart").click(function(){

     // this.prop('disabled', true);
     // $('#desctive').prop('disabled', false);

     let formData=new FormData();
        formData.append('msg','reset');
        const ip =$("#ip").val()
       
     axios({
          url:"http://"+ip+":80/message",
          method: "POST",
          data: formData,
        })
          .then((res) => {console.log(res)})
          .catch((err)=>console.log(err));
   }
   );
   