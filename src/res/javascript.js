//Main JavaScript File
var heartbeat_enabled = true;
var isFooterLocked = false;
var timer_msg_box;
var handle_load_monitor_table;

function boot()
{
	document.getElementById("server_address").value = window.location.host;
	open_message_box("Debugger Load Success!");
}

function colorize(comp)
{
	comp.style.backgroundColor = "#" + (Math.random() * 0xFFFFFF << 0).toString(16);
}

function loadAJAXGet(location, callback)
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function()
	{
		if(xhr.readyState == 4)
		{
			callback(xhr.responseText);
		}
	};

	xhr.open("POST", location, true);
	xhr.timeout = 4000;
	xhr.send();
}

function toggleHeartbeat()
{
	if(heartbeat_enabled)
	{
		heartbeat_enabled = false;
		document.getElementById("heartbeat_status").innerHTML = "Off";
		document.getElementById("heartbeat_status").style.color = "red";
	}
	else
	{
		heartbeat_enabled = true;
		document.getElementById("heartbeat_status").innerHTML = "On";
		document.getElementById("heartbeat_status").style.color = "#98BF21";
	}
}

function loadAJAXPost(location, data, callback)
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function()
	{
		if(xhr.readyState = 4)
		{
			callback(xhr.responseText);
		}
	};

	xhr.open("POST", location, true);
	xhr.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xhr.timeout = 4000;
	xhr.send(data);
}

function getAddr(url)
{
	return "http://" + document.getElementById("server_address").value + url;
}

function heartbeat()
{
	if(heartbeat_enabled)
	{
		var xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function()
		{
			if(xhr.readyState == 4)
			{
				document.getElementById("server_connected").style.right = "0px";
			}
		}

		xhr.open("POST", getAddr("/heartbeat"));
		xhr.timeout = 4000;

		xhr.ontimeout = function()
		{
			document.getElementById("server_connected").style.right = "-1000px";
		}

		xhr.onerror = function()
		{
			document.getElementById("server_connected").style.right = "-1000px";
		}

		xhr.send();
	}
}

setInterval(heartbeat, 4000);

function checkInetStatus(return_val)
{
	if(return_val != "N")
	{
		document.getElementById("inet_connected").style.right = "0px";
	}
	else
	{
		document.getElementById("inet_connected").style.right = "-1000px";
	}
}

function checkInet()
{
	if(heartbeat_enabled)
	{
		loadAJAXGet("/inet_check", checkInetStatus);
	}
}

function toggle_footer_lock()
{
	if(isFooterLocked)
	{
		document.getElementById("footer").style.right = "90%";
		document.getElementById("footer-locker").innerHTML = "Menu: Unlocked";
		open_message_box("Menu Unlocked!");
		isFooterLocked = false;
	}
	else
	{
		document.getElementById("footer").style.right = "10%";		
		document.getElementById("footer-locker").innerHTML = "Menu: Locked";
		open_message_box("Menu Locked!");
		isFooterLocked = true;
	}
}

function close_message_box()
{
	document.getElementById("msg_box").style.top = "-1000px";
	clearInterval(timer_msg_box);
}

function open_message_box(message)
{
	document.getElementById("msg_box").style.top = "32px";
	document.getElementById("msg_box_txt").innerHTML = message;
	clearInterval(timer_msg_box);
	timer_msg_box = setInterval(close_message_box, 2000);
}

function update_inject_status(x)
{
	open_message_box(x);
}

function send_inject_form()
{
	var x = "key=" + encodeURI(document.getElementById("input_key").value) + "&data=" + encodeURI(document.getElementById("input_value").value);
	loadAJAXPost(getAddr("/put_wf_new"), x, update_inject_status);
	open_message_box(x);
}

function load_monitor_table()
{
	monitor_form_table
	loadAJAXGet(getAddr("/monitor_tbl"), function(x){document.getElementById("monitor_form_table").innerHTML = x;});
}

function startMonitor()
{
	clearInterval(handle_load_monitor_table);
	handle_load_monitor_table = setInterval(load_monitor_table, 200);
	document.getElementById("start_loading_table").disabled = true;
	document.getElementById("stop_loading_table").disabled = false;
}

function stopMonitor()
{
	clearInterval(handle_load_monitor_table);
	document.getElementById("start_loading_table").disabled = false;
	document.getElementById("stop_loading_table").disabled = true;
}
// setInterval(checkInet, 4000);