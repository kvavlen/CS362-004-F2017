/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Natasha Kvavle
// kvavlen
// Extra Credit: Random URLValidator Test

import java.util.Random;

import junit.framework.TestCase;




/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

  
   public void testManualTest()
   {
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }

   // Reference: https://stackoverflow.com/questions/5887709/getting-random-numbers-in-java - used to determine how to write code in java to create random numbers
   
   public void testRandomTest()
   {
	   // Create UrlValidator object & Random Num Generator Object
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES); 
	   Random randomGen = new Random(); 
	   
	   // Define parts of URL that don't need to be generated with each iteration
	   
	   // PROTOCOL
	   // Reference: https://en.wikipedia.org/wiki/Application_layer
	   // 		     https://en.wikipedia.org/wiki/URL
	   String [] valid_protocol = {"http://", "https://", "ftp://", "file://", "data://"}; 
	   String [] invalid_protocol = {"", "://", "123://", "345://", "567://"}; 
	   
	   // AUTHORITY: DOMAIN
	   // Reference: https://en.wikipedia.org/wiki/Domain_name
	   // 		     https://en.wikipedia.org/wiki/Hostname
	   String [] valid_domain = {"www.example.com", "en.yesthisisaurl.com", "www.woopdedoo.us", "www.ohcanada.ca", "1ww.british.uk", "www.865309.edu", "www.thisismyjam.org" }; 
	   String [] invalid_domain = {"", "---.empty.com", "**.ex.com", "...www...com...", "&&&//www.badex.com", "w w.ex.com", "    w.com" };
	   	   
	   // PATH?QUERY
	   // Reference: https://en.wikipedia.org/wiki/Query_string
	   //			 https://en.wikipedia.org/wiki/URL
	   String [] valid_pathquery = {"/path?query=value", "/path?query", "/examplepath", "/path?query&query&query", "", "/example/example/example/exampleception"}; 
	   String [] invalid_pathquery = {"/////////", "_/_", "./path", "--/path", ">/path", "<<>>" }; 
	   
	   // Count how many test cases pass
	   int resultCount = 0; 
	   
	   // For 1000 iterations, test URLs that are made from random VALID & INVALID, parts (in the correct order) 
	   for (int i = 0; i < 100000; i++) {
		  
		   // Define parts of URL that should be generated each iteration
		   
		   // AUTHORITY: IP
		   // Reference: https://en.wikipedia.org/wiki/URL
		   //			 https://en.wikipedia.org/wiki/IPv4
		   int [] valid_ip = {0, 0, 0, 0}; 
		   int [] invalid_ip = {0, 0, 0, 0};
		   
		   for (int l = 0; l < 4; l++) {
			   
			   int valNum = randomGen.nextInt(255); 
			   int invalNum = randomGen.nextInt(1000000000) + 256;
			   
			   valid_ip[l] = valNum; 
			   invalid_ip[l] = invalNum; 
		   }
		  
		   // PORT
		   // Reference: https://stackoverflow.com/questions/113224/what-is-the-largest-tcp-ip-network-port-number-allowable-for-ipv4
		   int valid_port = randomGen.nextInt(65535); 
		   int invalid_port = randomGen.nextInt(10000000) + 65536; 

		   // Test VALID URLs ----------------------------------------------------------------------------------------------------------------------------------------------------
		   String url_under_test = ""; 
		  
		   // Get protocol
		   int b = randomGen.nextInt(5);
		   url_under_test += valid_protocol[b]; 
		    
		   // Randomly get domain or IP
		   int domain_or_ip = randomGen.nextInt(1);
		   int c = randomGen.nextInt(6); 
		   if (domain_or_ip == 0) {
			   url_under_test += valid_domain[c]; 
		   }
		   else { 
			   url_under_test += (valid_ip[0] + "." + valid_ip[1] + "." + valid_ip[2] + "." + valid_ip[3]);
		   }
		   
		   // Get port and path/query
		   int d = randomGen.nextInt(5); 
		   url_under_test += ":" + valid_port; 
		   url_under_test += valid_pathquery[d];
		   
		   // Test URL
		   System.out.println("URL UNDER TEST: " + url_under_test);
		   boolean checkTrue = validator.isValid(url_under_test);
		   System.out.println("Expected = true, Actual = " + checkTrue ); 
		   
		   if (checkTrue == true) {
			   resultCount += 1; 
		   }
		 
		   // Test INVALID URLs --------------------------------------------------------------------------------------------------------------------------------------------------
		   url_under_test = ""; 
		   
		   // Get Protocol
		   b = randomGen.nextInt(5);
		   url_under_test += invalid_protocol[b]; 
		    
		   // Get domain or IP 
		   domain_or_ip = randomGen.nextInt(1); 
		   c = randomGen.nextInt(6); 
		   if (domain_or_ip == 0) {
			   url_under_test += invalid_domain[c]; 
		   }
		   else { 
			   url_under_test += (invalid_ip[0] + "." + invalid_ip[1] + "." + invalid_ip[2] + "." + invalid_ip[3]);
		   }
		   
		   // Get port and path/query
		   d = randomGen.nextInt(5); 
		   url_under_test += ":" + invalid_port; 
		   url_under_test += invalid_pathquery[d];
		   
		   // Test URL
		   System.out.println("URL UNDER TEST: " + url_under_test);
		   boolean checkFalse = validator.isValid(url_under_test);
		   System.out.println("Expected = false, Actual = " + checkFalse ); 
		   
		   if (checkFalse == true) {
			   resultCount += 1; 
		   }
		 
		   // Test a combo of Invalid and Valid URL parts ------------------------------------------------------------------------------------------------------------------------
		   // Create an empty array 
		   int [] boolean_array = {0,0,0,0};
		   
		   // Fill array with a random combination of 1s and 0s to help us determine if a part of URL is valid or invalid
		   // 1 => VALID part 
		   // 0 => INVALID part 
		   for (int j = 0; j < 4; j++) {
			   int value = 0; 
			   
			   // If we aren't at the position of authority, choose between 0 and 1
			   if (j != 1) {
				   value = randomGen.nextInt(1);
			   }
			   // If we are at position of authority, then add 2nd option to provide random IP address (valid) 
			   // and third option to provide random IP address (invalid)
			   else {
				   value = randomGen.nextInt(3); 
			   }
			   
			   boolean_array[j] = value; 
		   }
		   
		   // For each integer in array, add to the URL either an invalid or valid part of the URL
		   // Count how many valid parts are added -- if count is 4 at the end of the manipulation
		   // then we know the URL should be valid. 
		   url_under_test = ""; 
		   int count = 0; 
		   
		   b = randomGen.nextInt(5);
		   // Invalid protocol
		   if (boolean_array[0] == 0) {
			   url_under_test += invalid_protocol[b];
		   }
		   // Valid protocol
		   else {
			   url_under_test += valid_protocol[b]; 
			   count += 1; 
		   }
		   
		   c = randomGen.nextInt(6); 
		   // Invalid domain
		   if (boolean_array[1] == 0) {
			   url_under_test += invalid_domain[c];
		   }
		   // Valid domain
		   else if (boolean_array[1] == 1){
			   url_under_test += valid_domain[c]; 
			   count += 1; 
		   } 
		   
		   // Valid IP address
		   else if (boolean_array[1] == 2) {
			   url_under_test += (valid_ip[0] + "." + valid_ip[1] + "." + valid_ip[2] + "." + valid_ip[3]); 
			   count += 1; 
		   }
		   // Invalid IP address
		   else if (boolean_array[1] == 3) {
			   url_under_test += (invalid_ip[0] + "." + invalid_ip[1] + "." + invalid_ip[2] + "." + invalid_ip[3]);
		   }
		    
		   // Invalid port
		   if (boolean_array[2] == 0) {
			   url_under_test += ":" + invalid_port;
		   }
		   // Valid port
		   else {
			   url_under_test += ":" + valid_port; 
			   count += 1; 
		   } 
		   
		   d = randomGen.nextInt(5); 
		   // Invalid path/query
		   if (boolean_array[3] == 0) {
			   url_under_test += invalid_pathquery[d];
		   }
		   // Valid path/query
		   else {
			   url_under_test += valid_pathquery[d];
			   count += 1; 
		   } 
		   
		   
		   // Test URL
		   System.out.println("URL UNDER TEST: " + url_under_test);
		   if(count == 4) {
			   checkTrue = validator.isValid(url_under_test);
			   System.out.println("Expected = true, Actual = " + checkTrue ); 
			   
			   if (checkTrue == true) {
				   resultCount += 1; 
			   }
		   }
		   else {
			   checkFalse = validator.isValid(url_under_test); 
			   System.out.println("Expected = false, Actual = " + checkFalse); 
			   
			   if (checkFalse == false) {
				   resultCount += 1; 
			   }
		   }
	   }
	   
	   // Assert that all tests passed
	   assertTrue(resultCount == 300000); 
   }

   

}
