
rder: 1px solid gray;
	border-collapse: collapse;
	//margin: 0 auto;
}
th,td {
	border: 1px solid gray;
	border-collapse: collapse;
	padding-left:10px;
    padding-right:10px;
	padding-top:10px;
	padding-bottom:10px;
	font-size: 12px;
	//border-style: hidden;
}
th {
	background-color:#F2F2F2;
}


#noborder{
	border-style: hidden;
}


button {
    background-color: #4CAF50;
    border: none;
    color: white;
    padding: 10px 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 14px;
    margin: 4px 2px;
    cursor: pointer;
}

select {
    height: 30px;
    padding-left: 10px;
    font-size: 12px;
    color: #08088A;
    border: 1px solid #08088A;
    border-radius: 3px;
}

#boldtable {
	font-weight:bold;
}


#linkentry {
	cursor:pointer;
	a:hover   { text-decoration:underline; color:#FF0000; }
}

</style>

<script>
var gTopObj;
var gXhttp;
var gOpenOption = 0;
var gLastTagId = ''; 


var isBroadcastMWPart = 1;

window.onload = function()
{
	var dvrParam;
	var urlParam = window.location.search.substring(1).split('&');
	if(	urlParam.length > 1)
	{
		//dvrParam = urlParam[1].split('=');
		//if(dvrParam.length == 2 && dvrParam[0] == 'dvr' && dvrParam[1] == 1) isDvrPartOnly = 1;
	}



	gTopObj = new Array();
	
	gXhttp = new XMLHttpRequest();
	var qSearchURL = "http://hlm.lge.com/issue/rest/api/2/search/";
	
	if(isBroadcastMWPart) 
		requestQuery = 'issuetype = Initiative   AND (labels=sungmo.yang and assignee in (ykwang.kim)) ORDER BY updatedDate DESC';
	else 
		requestQuery = 'issuetype = Initiative AND labels = 2018TBS ORDER BY updatedDate DESC';

	var param = {"jql": requestQuery ,"startAt":"0", "fields":["key", "assignee"]};
	gXhttp.onreadystatechange = OnHttpResult0;
	gXhttp.open("POST", qSearchURL , true);
	gXhttp.withCredentials = true;
  	gXhttp.setRequestHeader("Content-Type", "application/json; charset=utf-8"); 
  	gXhttp.send(JSON.stringify(param));
	InitSprintOption();
	document.querySelector('#sprint').addEventListener('change', UpdateTable);
	document.querySelector('#owner').addEventListener('change', UpdateTable);

	document.querySelector('#open_story').addEventListener('click' , OpenStoryClickHandler);
	document.querySelector('#open_story').addEventListener('mouseover' , function() {
		this.style.cursor = 'pointer';
	});
	document.querySelector('#open_story').addEventListener('mouseout' , function() {
		this.style.cursor = 'auto';
	});


	document.querySelector('#viewOpt').addEventListener('click' , function() {
		UpdateDetailTable(gLastTagId);
	});
}

function OpenStoryClickHandler()
{
	if(gOpenOption == 0)
	{
		gOpenOption = 1;
		document.querySelector('#open_story').innerHTML = '... ..';
	}
	else
	{
		gOpenOption = 0;
		document.querySelector('#open_story').innerHTML = '... ..';
	}
	UpdateDetailTable(gLastTagId);
}



function InitSprintOption()
{
	var week = 5;
	var sp_idx = 12;
	var days = new Date('2018-1-29');
	
	var insText = '<option value="ALL">' + 'ALL sprints' + '</option>';
	var today = new Date();
	var s = new Date();
	var e = new Date();


	//var debugString = '';

	while(days.getFullYear() != 2019)
	{
		var weeksLeap = getSpWeeks(sp_idx);
		s.setTime(days.getTime());
		days.setDate(days.getDate() + weeksLeap * 7 - 1);
		e.setTime(days.getTime());
		days.setDate(days.getDate() + 1);
		var weekStr = '';
		for(var i = 0 ; i < weeksLeap ; i++)
		{
			if(i > 0) weekStr += '/';
			weekStr += (week + i);
		}

		var sprintStr = 'SPRINT #' + sp_idx + '  :  ' + weekStr + 'W(' + getDateString(s) + '~' + getDateString(e) + ')';

		//debugString += 'start :' + getDateString(s) + ', end :' +  getDateString(e) + '<br />' ;
		
		if(today.getTime() >= s.getTime() &&  today.getTime() <= e.getTime())
		{
			insText += '<option value="TVSP' + sp_idx +'" selected>' + sprintStr + '</option>';
		}
		else
			insText += '<option value="TVSP' + sp_idx +'">' + sprintStr + '</option>';
		week+= weeksLeap;
		sp_idx++;
	}
	document.querySelector('#sprint').innerHTML = insText;

}

function getDateString(cur_day)
{
	var month = cur_day.getMonth()+1;  
	var day = cur_day.getDate();  
	var year = cur_day.getFullYear();  
	var result = year + '/' + month + '/' + day; 
	return result;
}


function getSpWeeks(sp_idx)
{
	if(sp_idx == 15) return 3;
	return 2;
}


function AddBaseKey(b_key)
{
	newObj = new Object();
	newObj.key = b_key;
	newObj.xhttp = new XMLHttpRequest();
	newObj.linkUrl = 'http://hlm.lge.com/issue/rest/api/2/issue/' + b_key;
	var subKey = b_key.split('-');
	newObj.xhttp.tagId = subKey[0] + subKey[1];
	
	gTopObj.push(newObj);
}


function OnHttpResult0()
{
	document.querySelector('#httpStatus').innerHTML = '... .. ..(0) : ' + this.readyState + '/' + this.status;
	if(this.readyState === 4 && this.status === 200)
	{
		//document.querySelector('#debug').innerHTML = this.responseText;
		var resultJSON = JSON.parse(this.responseText);
		var resultIssues = resultJSON.issues;
		for (var i in resultIssues) {
			AddBaseKey(resultIssues[i].key);
		}
		for(var i in gTopObj)
		{
  			gTopObj[i].xhttp.open("GET", gTopObj[i].linkUrl, true);
  			gTopObj[i].xhttp.withCredentials = true;
  			gTopObj[i].xhttp.setRequestHeader("Content-Type", "application/json; charset=utf-8");
			gTopObj[i].xhttp.onreadystatechange = OnHttpResult1;
		}
		InitOwnerFilter(resultIssues);

		for(var i in gTopObj)
		{
			gTopObj[i].xhttp.send();
		}
	}
}


function InitOwnerFilter(i_list)
{
	var ownerList = new Object();
	var innerText = '<option value="ALL" selected>All</option>';
	for(var i in i_list)
	{
		var tmp = i_list[i].fields.assignee.displayName.split(' ');
		var co = tmp[0];
		if(!(co in ownerList))
		{
			ownerList[co] = co;
		}
	}
	for(var i in ownerList)
	{
		innerText += '<option value="' + ownerList[i] + '">' + ownerList[i] + '</option>';
	}
	document.querySelector('#owner').innerHTML = innerText;
}

function OnHttpResult1()
{
	document.querySelector('#httpStatus').innerHTML = '... .. ..(1) : ' + this.readyState + '/' + this.status;
	if(this.readyState === 4 && this.status === 200)
	{
		var resultJson = JSON.parse(this.responseText);
		var tdObject = document.querySelector('#' + this.tagId);
		//document.querySelector('#debug').innerHTML = this.responseText;

		this.issueType = 'Initiative';
		this.linkAddr = resultJson.key;
		this.summary = resultJson.fields.summary;
		this.owner = 'unassigned';
		if(resultJson.fields.assignee && resultJson.fields.assignee.displayName)
		{
			var tmp = resultJson.fields.assignee.displayName.split(' ');
			this.owner = tmp[0];
		}
		this.statusImg = resultJson.fields.status.iconUrl;
		this.statusName = resultJson.fields.status.name;
		this.bShowEpic = 0;
		var tmp = this.linkAddr.split('-');
		this.id = tmp[0] + tmp[1];

		this.EpicList = new Array();
		var issuelinks = resultJson.fields.issuelinks;
		var qSearchURL = "http://hlm.lge.com/issue/rest/api/2/search/";
		for(var i in issuelinks)
		{
			if(issuelinks[i].outwardIssue && issuelinks[i].outwardIssue.fields.issuetype.name == 'Epic')
			{
				var newEpicItem = new Object;
				newEpicItem.summary = issuelinks[i].outwardIssue.fields.summary;
				newEpicItem.issueType = 'epic';
				newEpicItem.linkAddr = issuelinks[i].outwardIssue.key;
				newEpicItem.bShowStory = 0;
				tmp = newEpicItem.linkAddr.split('-');
				newEpicItem.id = tmp[0] + tmp[1];
				newEpicItem.owner = 'unknown';

				newEpicItem.statusImg = issuelinks[i].outwardIssue.fields.status.iconUrl;
				newEpicItem.statusName = issuelinks[i].outwardIssue.fields.status.name;

				newEpicItem.xhttp = new XMLHttpRequest();
				var story_search_query = '"Epic Link"="' + newEpicItem.linkAddr + '"';
				newEpicItem.param = {"jql": story_search_query,"startAt":"0", "maxResults":"2000", "fields":["summary","key","status", "issuetype", "assignee", "labels", "customfield_10002", "timetracking", "customfield_10005"]};
	  			newEpicItem.xhttp.open("POST",qSearchURL, true);
  				newEpicItem.xhttp.withCredentials = true;
  				newEpicItem.xhttp.setRequestHeader("Content-Type", "application/json; charset=utf-8");
				newEpicItem.xhttp.onreadystatechange = OnHttpResult2;
				newEpicItem.xhttp.recvResult = 0;
				
				// EPIC . Onwer . ... .. ....... ..
				var linkurl2 = 'http://hlm.lge.com/issue/rest/api/2/issue/' + newEpicItem.linkAddr;
				newEpicItem.xhttp2 = new XMLHttpRequest();

  				newEpicItem.xhttp2.open("GET", linkurl2 , true);
  				newEpicItem.xhttp2.withCredentials = true;
  				newEpicItem.xhttp2.setRequestHeader("Content-Type", "application/json; charset=utf-8");
				newEpicItem.xhttp2.onreadystatechange = OnHttpResult2_2;
				newEpicItem.xhttp2.recvResult = 0; 
				newEpicItem.xhttp2.parent = newEpicItem;
				this.EpicList.push(newEpicItem);
				UpdateRecvStatus();
			}
		}
		for(var i in this.EpicList)
		{
			this.EpicList[i].xhttp.send(JSON.stringify(this.EpicList[i].param));
			//this.EpicList[i].xhttp2.send();
		}
		UpdateTable();
	}
}

function OnHttpResult2_2()
{
	document.querySelector('#httpStatus').innerHTML = '... .. ..(2) : ' + this.readyState + '/' + this.status;
	if(this.readyState === 4 && this.status === 200)
	{
		var resultJson = JSON.parse(this.responseText);
		var resultIssues = resultJson.issues;
		//document.querySelector('#debug').innerHTML = this.responseText;

		if(resultJson.fields.assignee && resultJson.fields.assignee.displayName)
		{
			var tmp = resultJson.fields.assignee.displayName.split(' ');
			this.parent.owner = tmp[0];
		}
		this.recvResult = 1;
		//UpdateRecvStatus();
		UpdateDetailTable(gLastTagId);
	}
}


function OnHttpResult2()
{
	document.querySelector('#httpStatus').innerHTML = '... .. ..(2) : ' + this.readyState + '/' + this.status;
	if(this.readyState === 4 && this.status === 200)
	{
		var resultJson = JSON.parse(this.responseText);
		var resultIssues = resultJson.issues;
		this.recvResult = 1;

		this.StoryList = new Array();
		UpdateRecvStatus();

		for (var issue in resultIssues) 
		{
			var fields = resultIssues[issue].fields;
          	var key = resultIssues[issue].key;
          	var summary = fields.summary;
          	var status = fields.status.name;

			var newStoryItem = new Object;
			newStoryItem.summary = fields.summary;
			newStoryItem.issueType = 'story';
			newStoryItem.linkAddr = resultIssues[issue].key;
			newStoryItem.id = 'TBD';
			newStoryItem.owner = 'unassigned';
			newStoryItem.timeTracking = fields.timetracking;
			newStoryItem.sprint = 'NA';
			if( fields.customfield_10005 )
			{
				var tmp = fields.customfield_10005[0];
				var s = tmp.indexOf('name=');
				var tmp2 = tmp.substring(tmp.indexOf('name=')).split(',');
				newStoryItem.sprint = tmp2[0].substring(5);
			}
			

			if(fields.assignee && fields.assignee.displayName)
			{
				var tmp = fields.assignee.displayName.split(' ');
				newStoryItem.owner = tmp[0];
			}
			newStoryItem.statusImg = fields.status.iconUrl;
			newStoryItem.statusName = fields.status.name;
			
			newStoryItem.storyPoint = 'TBD';
			if(fields.customfield_10002) newStoryItem.storyPoint = fields.customfield_10002;

			this.StoryList.push(newStoryItem);
		}
		UpdateTable();
	}	
}


var gTableHeader = '<tr><th>Issue Type</th><th>Key</th><th>Summary</th><th>Status</th><th>Owner</th><th>EPIC</th><th>Story</th><th>Story #cur</th><th>..SP</th><th>..SP</th><th>SP...</th><th>...</th><th>S-ID</th></tr>';

function UpdateTable()
{
	var sObjSprint = document.querySelector('#sprint');
	var sObjSprintValue = sObjSprint.options[sObjSprint.selectedIndex].value;


	var sObjOwner = document.querySelector('#owner');
	var sObjOwnerValue = sObjOwner.options[sObjOwner.selectedIndex].value;


	//document.querySelector('#debug').innerHTML = JSON.stringify(gTopObj);
	var innerText = gTableHeader;
	var eventListenerList = new Array();


	
	var statisticObject = new Object();
	for(var i in gTopObj)
	{
		if(!('xhttp' in gTopObj[i])) continue;
		if(!('EpicList' in gTopObj[i].xhttp)) continue;
		if(!('tagId' in gTopObj[i].xhttp)) continue;

		gTopObj[i].xhttp.nrEpic = 0;
		gTopObj[i].xhttp.nrStory = 0;
		gTopObj[i].xhttp.nrStoryCurrent = 0;
		gTopObj[i].xhttp.spEstimate = 0;
		gTopObj[i].xhttp.spConsumed = 0;
		gTopObj[i].xhttp.nrDone = 0;

		var epicList = gTopObj[i].xhttp.EpicList;
			
		for(var j in epicList)
		{
			epicList[j].nrStory = 0;
			epicList[j].nrStoryCurrent = 0;
			epicList[j].spEstimate = 0;
			epicList[j].spConsumed = 0;
			epicList[j].spRatio = 0;
			epicList[j].nrDone = 0;
			if(!('StoryList' in epicList[j].xhttp)) continue;
			var storyList = epicList[j].xhttp.StoryList;
			epicList[j].nrStory = storyList.length;
			for(var k in storyList)
			{
				storyList[k].spEstimate = 0;
				storyList[k].spConsumed = 0;
				storyList[k].spRatio = 0;
				if(storyList[k].timeTracking)
				{
					if('originalEstimateSeconds' in storyList[k].timeTracking)
					{
						storyList[k].spEstimate = storyList[k].timeTracking.originalEstimateSeconds;
					}
					if('timeSpentSeconds' in storyList[k].timeTracking)
					{
						storyList[k].spConsumed = storyList[k].timeTracking.timeSpentSeconds ;
					}
					if(storyList[k].spEstimate)
					{
						storyList[k].spRatio = ( storyList[k].spConsumed / storyList[k].spEstimate ) * 100;
					}
				}
				if(storyList[k].sprint.indexOf(sObjSprintValue) != -1 || sObjSprintValue == 'ALL')
				{
					epicList[j].spEstimate += storyList[k].spEstimate;
					epicList[j].spConsumed += storyList[k].spConsumed;
				
					gTopObj[i].xhttp.nrStoryCurrent++;
					epicList[j].nrStoryCurrent++;


					if(storyList[k].statusName == 'Resolved' || storyList[k].statusName == 'Closed')
					{
						gTopObj[i].xhttp.nrDone++;
						epicList[j].nrDone++;
					}
				}
			}
			if(epicList[j].spEstimate)
			{
				epicList[j].spRatio = (epicList[j].spConsumed / epicList[j].spEstimate) * 100;
			}
			gTopObj[i].xhttp.nrStory += epicList[j].nrStory;
			gTopObj[i].xhttp.spEstimate += epicList[j].spEstimate;
			gTopObj[i].xhttp.spConsumed += epicList[j].spConsumed;
		}
		gTopObj[i].xhttp.nrEpic = epicList.length;
		
		gTopObj[i].xhttp.spRatio = 0;
		if(gTopObj[i].xhttp.spEstimate)
		{	
			gTopObj[i].xhttp.spRatio = (gTopObj[i].xhttp.spConsumed / gTopObj[i].xhttp.spEstimate) * 100;
		}

		if(gTopObj[i].xhttp.owner.indexOf(sObjOwnerValue) != -1 || sObjOwnerValue == 'ALL')
		{
			eventListenerList.push(gTopObj[i].xhttp.tagId);
			innerText += GetTableEntry(gTopObj[i].xhttp, 1, 'black');


			var statusName = gTopObj[i].xhttp.statusName;
			if(statusName in statisticObject) statisticObject[statusName]++;
			else statisticObject[statusName] = 1;
		}
	}
	document.querySelector('#init_summary').innerHTML = innerText;


	var sortable = [];
	for (var i in statisticObject) {
    	sortable.push([i, statisticObject[i]]);
	}

	sortable.sort(function(a, b) {
   		return a[1] - b[1];
	});


	var sTextItem = '<tr>';
	var sTextCount = '<tr>';
	var curInitCnt = 0;
	for(var i in sortable)
	{
		sTextItem += '<th>' + sortable[i][0] + '</th>';
		sTextCount += '<td>' + sortable[i][1] + '</td>';
		curInitCnt += sortable[i][1];
	}
	sTextItem += '<th> TOTAL </th></tr>';
	sTextCount += '<td>' + curInitCnt + '</td></tr>';
	document.querySelector('#init_statistics').innerHTML = sTextItem + sTextCount;

	for(var i in eventListenerList)
	{
		document.querySelector('#' + eventListenerList[i]).addEventListener('click' , initiativeHandler);
		document.querySelector('#' + eventListenerList[i]).addEventListener('mouseover' , function() {
			this.style.cursor = 'pointer';
		});
		document.querySelector('#' + eventListenerList[i]).addEventListener('mouseout' , function() {
			this.style.cursor = 'auto';
		});
	}
}
function GetTableEntry(issue_obj, need_pagelink, desc_color)
{
	var activateColor = '#0B6121';
	var unactColor = '#BDBDBD';

	var result = '';
	var fullAddr = 'http://hlm.lge.com/issue/browse/' + issue_obj.linkAddr;
	var id = '';


	var herf_s ='';
	var herf_e = '';
	if(need_pagelink)
	{
		id = 'id = "' + issue_obj.tagId + '"';
		if(issue_obj.nrStoryCurrent)
			herf_s = '<a href="#detail_spec" style="color:' + activateColor + '">';
		else
			herf_s = '<a href="#detail_spec" style="color:' + unactColor + '">';
		herf_e = '</a>';
	}
	var nrEpic = '';
	var nrStory = '';
	var nrStoryCurrent = '';
	var spEstimate = 0;
	var spConsumed = 0;
	var ratio =  parseFloat(issue_obj.spRatio.toFixed(1)) + '%' ;
	var progress = '';
	var sprintID = '';

	var issue_style = '';


	var iconText = '';
	if(issue_obj.issueType == 'Initiative')
	{
		nrEpic = issue_obj.nrEpic;
		nrStory = issue_obj.nrStory;
		nrStoryCurrent = issue_obj.nrStoryCurrent;


		if(issue_obj.nrStoryCurrent)
		{
			var tmpProg = (issue_obj.nrDone / issue_obj.nrStoryCurrent) * 100 ;
			progress = parseFloat(tmpProg.toFixed(1)) + '%';
		}
		iconText = '<img src="http://hlm.lge.com/issue/secure/viewavatar?size=xsmall&avatarId=15912&avatarType=issuetype">';
	}
	if(issue_obj.issueType == 'epic')
	{
		nrStory = issue_obj.nrStory;
		nrStoryCurrent = issue_obj.nrStoryCurrent;
		issue_style  = 'style="background-color:#F5BCA9"';	
		if(nrStoryCurrent == 0) ratio = 'Sprint...';


		if(issue_obj.nrStoryCurrent)
		{
			var tmpProg = (issue_obj.nrDone / issue_obj.nrStoryCurrent) * 100 ;
			progress = parseFloat(tmpProg.toFixed(1)) + '%';
		}
		iconText = '<img src="http://hlm.lge.com/issue/images/icons/issuetypes/epic.png">';
	}


	if(issue_obj.issueType == 'Initiative' || issue_obj.issueType == 'epic')
	{
		var bgColor;
		if(issue_obj.issueType == 'Initiative') bgColor = '#ECE0F8';
		else bgColor = '#A9F5A9';

		if(nrStoryCurrent == 0)
		{
			issue_style  = 'style="background-color:' + bgColor + ' ; color:' + unactColor + '"';	
			ratio = 'Sprint...';
		}
		else
		{
			issue_style  = 'style="background-color:' + bgColor + ' ; font-weight: bold ; color:' + activateColor + '"';	
		}
	}
	if(issue_obj.issueType == 'story')
	{
		sprintID = issue_obj.sprint;
		iconText = '<img src="http://hlm.lge.com/issue/images/icons/issuetypes/story.png">';


		issue_style  = 'style="color:' + desc_color + '"';	
	}

	result += '<tr ' + issue_style + '>' +
					'<td>'+ iconText + ' ' + issue_obj.issueType + '</td>' +
					'<td><a href="' + fullAddr + '" target="_blank">' + issue_obj.linkAddr + '</a></td>' +
					'<td ' + id + '>' + herf_s + issue_obj.summary + herf_e + '</td>' +
					'<td><img src="' + issue_obj.statusImg + '">' + issue_obj.statusName + '</td>' +
					'<td>' + issue_obj.owner + '</td>' +
					'<td>' + nrEpic  + '</td>' +
					'<td>' + nrStory + '</td>' +
					'<td>' + nrStoryCurrent + '</td>' +
					'<td>' + parseFloat((issue_obj.spEstimate / 14400).toFixed(3)) + '</td>' +
					'<td>' + parseFloat((issue_obj.spConsumed / 14400).toFixed(3)) + '</td>' +
					'<td>' + ratio + '</td>' +
					'<td>' + progress + '</td>' +
					'<td>' + sprintID + '</td>' +
					'</tr>'
	return result;
}

function initiativeHandler()
{
	var clickID = this.getAttribute('id');
	//alert(clickID);
	gOpenOption = 0;
	document.querySelector('#open_story').innerHTML = '... ..';
	UpdateDetailTable(clickID);

	var curOwnerList = new Object();
	for(var i in gTopObj)
	{
		if(gTopObj[i].xhttp)
		{
			if(gTopObj[i].xhttp.id == clickID)
			{
				var targetObj = gTopObj[i].xhttp;

				for(var j in targetObj.EpicList)
				{
					if(targetObj.EpicList[j].xhttp2.recvResult == 0)
						targetObj.EpicList[j].xhttp2.send();
					var storyList = targetObj.EpicList[j].xhttp.StoryList;
					for(var k in storyList)
					{
						curOwnerList[storyList[k].owner] = 1;
					}
				}
				break;
			}
		}
	}
	var storyOwnerSelectObj = document.querySelector('#story_owner');
	var innerText = '<option value="ALL" selected> All </option>';

	var sortedOwnerList = new Array();
		
	for(var i in  curOwnerList)
	{
		sortedOwnerList.push(i);
	}
	sortedOwnerList.sort();

	for(var i in  sortedOwnerList)
	{
		innerText += '<option value="' + sortedOwnerList[i] + '"> ' + sortedOwnerList[i] + ' </option>';
	}
	storyOwnerSelectObj.innerHTML = innerText;
	
	storyOwnerSelectObj.addEventListener('change' , function() {
		UpdateDetailTable(gLastTagId);
	});
	//document.querySelector('#debug').innerHTML = JSON.stringify(curOwnerList);


}

function UpdateDetailTable(tagId)
{
	var sObjSprint = document.querySelector('#sprint');
	var sObjSprintValue = sObjSprint.options[sObjSprint.selectedIndex].value;

	var sObjViewOption = document.querySelector('#viewOpt').checked;


	var curOwner = document.querySelector('#story_owner');
	
	var curOwnerValue;
	if(curOwner.selectedIndex == -1)
		curOwnerValue = 'ALL';
	else
		curOwnerValue = curOwner.options[curOwner.selectedIndex].value;



	//alert(sObjViewOption.checked);
	gLastTagId = tagId;
	var innerText = gTableHeader ;
	for(var i in gTopObj)
	{
		if(!('xhttp' in gTopObj[i])) continue;
		if(!('EpicList' in gTopObj[i].xhttp)) continue;
		if(!('tagId' in gTopObj[i].xhttp)) continue;
		
		if(	gTopObj[i].xhttp.tagId == tagId)
		{
			innerText += GetTableEntry(gTopObj[i].xhttp, 0, 'black');
			var epicList = gTopObj[i].xhttp.EpicList;
			for(var j in epicList)
			{
				innerText += GetTableEntry(epicList[j], 0, 'black');
				if(gOpenOption)
				{
					var storyList = epicList[j].xhttp.StoryList;
					for(var k in storyList)
					{
						//if(storyList[k].sprint.indexOf(sObjSprintValue) != -1 || sObjSprintValue == 'ALL')
						var bShowStoryResult = bShowStory(sObjSprintValue, storyList[k] , sObjViewOption);
						if(bShowStoryResult)
						{
							var EntryColor = 'black';
							if(bShowStoryResult == 2) EntryColor = '#FE2EF7'; // ... Story


							if(storyList[k].statusName == 'Closed') EntryColor = '#04B404';
							
							if(curOwnerValue != 'ALL')
							{
								if(storyList[k].owner != curOwnerValue) EntryColor = '#E6E6E6';
							}
							innerText += GetTableEntry(storyList[k], 0, EntryColor);
						}
					}
				}
			}
			document.querySelector('#detail_view').innerHTML = innerText;
		}
	}
}

function bShowStory(curSelSprint , curStory , viewOpt)
{
	if(curSelSprint == 'ALL') return 1;
	if(viewOpt) // Close .. .. Sprint . ..
	{
		var curSelectSprintNumber = Number(curSelSprint.substring(4));
		for(var i = 12 ; i < curSelectSprintNumber ; i++)
		{
			var sprintString = 'TVSP' + i;
			if(curStory.sprint.indexOf(sprintString) != -1)
			{
			 	if(curStory.statusName != 'Closed') return 2;
				break;
			}
		}
	}
	if(curStory.sprint.indexOf(curSelSprint) != -1) return 1;
	return 0;
}



function UpdateRecvStatus()
{
	var rTotal = 0;
	var rCur = 0;
	
	for(var i in gTopObj)
	{		
		if(gTopObj[i].xhttp)
		{
			var epicList = gTopObj[i].xhttp.EpicList;
			for(var j in epicList)
			{
				//rTotal += 2;
				rTotal++;
				rCur += epicList[j].xhttp.recvResult ;
				//rCur += epicList[j].xhttp2.recvResult ;
			}
		}
	}
	//document.querySelector('#send_recv').innerHTML = '.. .. ..:' + rTotal + ', .. ..:' + rCur ;
	
	var progress = 0;
	if(rTotal) 
	{
		progress = (rCur / rTotal) * 100;
	}

	document.querySelector('#send_recv').innerHTML = '..... .... .:' + progress.toFixed() + '% (' + rTotal + '/' + rCur + ')';
}
</script>


<h5 id = 'httpStatus'>... .. .</h5>
<h5 id = 'send_recv'>.. ... .....</h5>
<h6> IE Brower ... ..... ... .. . ..... Chrome Browser .. ..... <h6>
<h6> HTTP .. ... 400 . .. HLM Session Login . . ..... ....</h6>
<br>
<h3> 1. CDP .. .. ..</h3>
<hr />


<table id='noborder'>
	<tr>
		<td id='noborder'> SPRINT </td>
		<td id='noborder'>
			<select id='sprint'>
			</select>
		</td>
		<td id='noborder'> OWNER </td>
		<td id='noborder'>
			<select id='owner'>
			</select>
		</td>
	</tr>
</table>

<br>
<table id='init_statistics'></table>
<br>
<table id='init_summary'></table>
<h3><a name='detail_spec'> 2. .. ..</a></h3>
<table id='noborder'><tr>
<td id='noborder'><h6 id='open_story'>... ..</h6></td>
<td id='noborder'>.... .. Story ..<input type="checkbox" id='viewOpt'></td>
<td id='noborder'>owner</td>
<td id='noborder'>
	<select id='story_owner'>
		<option value="ALL" selected> All </option>
	</select>
</td></tr></table>


<hr />
<table id='detail_view'></table>
<h3 id='debug'></h3>

