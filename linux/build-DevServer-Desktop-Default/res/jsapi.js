//This is the JavaScript API for the DevServer!
var server = window.location.host;
function setServer(location)
{
	server = location;
}

function get(key)
{
	var mutex = true;
	var value;
	try
	{
		var AJAX = new XMLHttpRequest();
		AJAX.onreadystatechange = function()
		{
			if(AJAX.readyState == 4)
			{
				value = AJAX.responseText;
				mutex = false;
			}
		};

		AJAX.onerror = function()
		{
			return "";
		}

		AJAX.open("POST", server, true);
		AJAX.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		AJAX.timeout = 4000;
		AJAX.send("key="encodeURI(key));

		//Wait for the response
		while(!mutex)
		{
			//Awaiting Response. Shouldn't take too long!
		}

		return value;
	}
	catch(exception)
	{
		//Something wierd happened!
		mutex = false;
		return "";
	}
}

function put(key, value)
{
	var AJAX = new XMLHttpRequest();
	AJAX.open("POST", server, true);
	AJAX.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	AJAX.timeout = 4000;
	AJAX.send("key=" + encodeURI(key) + "&data=" + encodeURI(value));
}