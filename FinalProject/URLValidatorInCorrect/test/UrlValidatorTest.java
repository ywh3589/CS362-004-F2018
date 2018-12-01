

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
   
	private final boolean printStatus = false;
  
   public UrlValidatorTest(String testName) {
      super(testName);
   }


   
   public void testManualTest()
   {
       boolean result;
       //test various valid and invalid strings
       String[] valid = {"http://www.google.com", "http://www.google.com/", "http://www.google.com/test1", 
                         "http://www.google.com/test1/", "http://www.google.com/test1/file", "http://www.google.com?action=view",
                         "ftp://0.0.0.0", "ftp://255.255.255.255", "h3t://go.au:65535", "h3t://go.au/$23", "h3t://go.au/$23?action=view"};
       String[] invalid = {"", "http:", "://go.com", "www.google.com:-1", "http:/go.com", "://:0/test1?action=view",
                           "3ht://go.a:-1", "http://.aaa", "ftp://255.com:65a/t123", "1.2.3.4.5:0?action=view"};
       
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.print("Testing valid urls: \n");
       //Reference: Piazza post @176 for continuing the tests after hitting IllegalArgumentException
       for (String url : valid) {
           result = false;
           try
           {
               result = urlVal.isValid(url);
           }
           catch(Error e)
           {
               System.out.print("ERROR! ");
           }
           if (!result) {
               System.out.print(url + "\n");
           }
       }
       
       System.out.print("Testing invalid urls: \n");
       for (String url : invalid) {
           result = false;
           try
           {
               result = !urlVal.isValid(url);
           }
           catch(Error e)
           {
               System.out.print("ERROR! ");
           }
           if (!result) {
               System.out.print(url + "\n");
           }
       }
   }
   
   public void testManualScheme()
   {
       //set our own schemes and test them
       String[] schemes = {"a", "ab", "c1", "z5p"};
       UrlValidator urlVal = new UrlValidator(schemes, 0);
       
       String[] invalid = {"http", "http://", "ftp", "c2", "ac", "z6p", "0", "HTTP", ""};
       
       System.out.print("Testing valid schemes: \n");
       for (String scheme : schemes) {
           if (!urlVal.isValidScheme(scheme)) {
               System.out.print(scheme + "\n");
           }
       }
       
       System.out.print("Testing invalid schemes: \n");
       for (String scheme : invalid) {
           if (urlVal.isValidScheme(scheme)) {
               System.out.print(scheme + "\n");
           }
       }       
   }
   
      public void testDebug()
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       assertTrue(!urlVal.isValid("http:go.com"));
   }
   
   public void testDebugScheme()
   {
       String[] schemes = {"a", "ab", "c1", "z5p"};
       UrlValidator urlVal = new UrlValidator(schemes, 0);
       
       assertTrue(urlVal.isValidScheme(schemes[3]));
   }
   
   
   //public class UrlValidatorPartitionTester extends TestCase {

	//   public UrlValidatorPartitionTester(String name) {
//	      super(name);
	//   }

	   // We will test with three different styles of input partitioning
	   // First, with All Valid vs. All Invalid vs. Mixed Valid and Invalid URL components
	   // Second, we will test with inputs partitioned into all valid URL components, and in correct order vs all valid URL components in the incorrect order
	   // Lastly we will test with inputs partitioned into Schemes Valid/Invalid, Authority Valid/Invalid, Path Valid/Invalid, and Query Valid/Invalid
	   
	   
	   // isValid should return true for all of the following inputs, which have every URL component valid
	   public void testAllValid()
	   {
		   UrlValidator allValidValidator = new UrlValidator(null, null,0);
		   assertTrue(allValidValidator.isValid("https://www.google.com"));
		   assertTrue(allValidValidator.isValid("https://www.facebook.com"));
		   assertTrue(allValidValidator.isValid("https://www.wikipedia.org"));
		   assertTrue(allValidValidator.isValid("http://www.agar.io"));
	   }
	   
	   
	   // isValid should  return false for all of the following inputs, which have every URL component invalid
	   public void testAllInvalid()
	   {
		   UrlValidator allInvalidValidator = new UrlValidator(null, null,0);
		   assertFalse(allInvalidValidator.isValid("htps://wwww.go-4le.coadm"));
		   assertFalse(allInvalidValidator.isValid("ftpss://wdw.!04._com"));
		   assertFalse(allInvalidValidator.isValid("https://www.wikipe!dia.org/!_.xt!"));
		   assertFalse(allInvalidValidator.isValid("http://w_w_w.agar.io"));
	   }
	   
	   // isValid should return false for all of the following inputs (which have valid URL components mixed with invalid ones)
	   public void testMixedValidInvalid() {
		   UrlValidator mixedValidInvalidValidator = new UrlValidator(null, null,0);
		   
		   assertFalse(mixedValidInvalidValidator.isValid("https://w5w.google.compd"));
		   assertFalse(mixedValidInvalidValidator.isValid("_5f://www.$!$D.com"));
		   assertFalse(mixedValidInvalidValidator.isValid("%4://www.wikipedia.org"));
		   assertFalse(mixedValidInvalidValidator.isValid("http://www._agar.dio"));
	   }
	   
	   // isValid should return true for all of the following inputs (which have valid URL components and in the correct order)
	   public void testInOrderValid()
	   {
		   UrlValidator inOrderValidator = new UrlValidator(null, null,0);
		   assertTrue(inOrderValidator.isValid("https://www.google.com:80"));
		   assertTrue(inOrderValidator.isValid("https://www.facebook.com/users.php"));
		   assertTrue(inOrderValidator.isValid("https://www.wikipedia.org"));
		   assertTrue(inOrderValidator.isValid("http://www.agar.io"));
		   
	   }
	   
	// isValid should return false for all of the following inputs (which have valid URL components but in the incorrect order)
	   public void testOutOfOrderValid()
	   {
		   UrlValidator inOrderValidator = new UrlValidator(null, null,0);
		   assertFalse(inOrderValidator.isValid("https://google.com.www"));
		   assertFalse(inOrderValidator.isValid("com://www.facebook.https"));
		   assertFalse(inOrderValidator.isValid("https://org.wikipedia.www"));
		   assertFalse(inOrderValidator.isValid("www://agar.io.h3t"));
	   }
	   
	   // isValid should return false for all of the following inputs (which have all invalid schemes combined with valid URL components)
	   public void testSchemePartition()
	   {
	        UrlValidator schemeValidator = new UrlValidator(null, null, 0);
	        
	        assertFalse(schemeValidator.isValid("ht4134tp://twitter.com"));
	        assertFalse(schemeValidator.isValid("ftpp://youtube.com/home"));
	        assertFalse(schemeValidator.isValid("h64t://amazon.com/products"));
	        assertFalse(schemeValidator.isValid("hf_tp:/netflix.com"));
	        assertFalse(schemeValidator.isValid("ptth/twitter.com:9000"));
	        assertFalse(schemeValidator.isValid("::://twitter.com"));
	   }

	   // isValid should return false for all of the following inputs, which have invalid authorities only
	   public void testAuthortiyPartition()
	   {
		UrlValidator authorityValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		assertFalse(authorityValidator.isValid(".com"));
		assertFalse(authorityValidator.isValid("https://www.!_d.com/files"));
		assertFalse(authorityValidator.isValid("http://!!!.$$$.%%%/download.html"));
		assertFalse(authorityValidator.isValid("https://ww_.health.net"));
		assertFalse(authorityValidator.isValid("google.!om"));
		assertFalse(authorityValidator.isValid("h3t://wwx.wow.3j"));
	   }

	   // isValid should return false for all of the following inputs, which have invalid paths only
	   public void testPathPartition()
	   {
		UrlValidator pathValidator = new UrlValidator(null, null, 0);
		assertFalse(pathValidator.isValid("http://www.amazon.com///////"));
		assertFalse(pathValidator.isValid("https://facebook.com/,///"));
		assertFalse(pathValidator.isValid("http://twitter.com//.7?q=/homework"));
		assertFalse(pathValidator.isValid("https://netflix.com/,..//image.png"));
			
	   }

	   // isValid should return true for all of the following inputs, which have valid queries only
	   public void testQueryPartition()
	   {
		UrlValidator queryValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		assertTrue(queryValidator.isValid("http://amazon.com/search?q=test"));
		assertTrue(queryValidator.isValid("http://twitter.com/search?user=10348234"));
	   }

	   // isValid should return false for all of the following inputs, which have invalid paths only
	   public void testIsValid()
	   {

		System.out.println("Tests Completed.");
	   }
//	}   
 
   
   
  //Programming based testing
  //to test isValid based on programming based testing
  //we can test testIsValidScheme, testIsValidAuthority, testIsValidPath, testIsValidQuery methods
   
   public void testIsValidScheme() {
	      if (printStatus) {
	         System.out.print("\n testIsValidScheme() ");
	      }
	      //String[] schemes = {"http", "file", "ftp://", "h3t://", ""};
	      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
	      //UrlValidator urlVal = new UrlValidator(schemes, 0);
	    
	      UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	     for (int sIndex = 0; sIndex < testScheme.length; sIndex++) {
	         ResultPair testPair = testScheme[sIndex];
	         boolean result = urlVal.isValidScheme(testPair.item);
	         System.out.print("\n\n values\n ");
	         System.out.println(testPair.item);
	         System.out.println(testPair.valid);
	         System.out.println(result);
	        	         
	         assertEquals(testPair.item, testPair.valid, result);
	         if (printStatus) {
	            if (result == testPair.valid) {
	               System.out.println('.');
	               System.out.println(testPair.item);
	            } else {
	               System.out.println('X');
	            }
	         }
	      }
	      if (printStatus) {
	         System.out.println();
	      }

	   }

   public void testIsValidAuthority() {
	      if (printStatus) {
	         System.out.print("\n testIsValidAuthority() ");
	      }
	//      String[] schemes = {"www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com"};
	      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
//	      UrlValidator urlVal = new UrlValidator(schemes, 0);
	      UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	     for (int sIndex = 0; sIndex < testAuthority.length; sIndex++) {
	         ResultPair testPair = testAuthority[sIndex];
	         boolean result = urlVal.isValidAuthority(testPair.item);
	         System.out.print("\n\n values\n ");
	         System.out.println(testPair.item);
	         System.out.println(testPair.valid);
	         System.out.println(result);
	         
	         System.out.print("\n\n\n\n");
	         
	         assertEquals(testPair.item, testPair.valid, result);
	         if (printStatus) {
	            if (result == testPair.valid) {
	            	System.out.print("inside isValid");
	      
	         //      System.out.println('.');
	               System.out.println(testPair.item);
	            } else {
	               System.out.println('X');
	            }
	         }
	      }
	      if (printStatus) {
	         System.out.println();
	      }

	   }


   
   
   public void testIsValidPath() {
	      if (printStatus) {
	         System.out.print("\n testIsValidPath() ");
	      }
	      //String[] schemes = {"/test1", "/t123", "/$23", "/test1/", "/test1/file", ""};
	      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
	      //UrlValidator urlVal = new UrlValidator(schemes, 0);
	      UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	     for (int sIndex = 0; sIndex < testPath.length; sIndex++) {
	         ResultPair testPair = testPath[sIndex];
	         boolean result = urlVal.isValidPath(testPair.item);
	         System.out.print("\n\n values\n ");
	         System.out.println(testPair.item);
	         System.out.println(testPair.valid);
	         System.out.println(result);
	         
	           
	         assertEquals(testPair.item, testPair.valid, result);
	         if (printStatus) {
	            if (result == testPair.valid) {
	            	
	                System.out.println('.');
	               System.out.println(testPair.item);
	            } else {
	               System.out.println('X');
	            }
	         }
	      }
	      if (printStatus) {
	         System.out.println();
	      }

	   }
   
   public void testIsValidQuery() {
	      if (printStatus) {
	         System.out.print("\n testIsValidAuthority() ");
	      }
	      //String[] schemes = {"?action=view", "?action=edit&mode=up", ""};
	      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
	      //UrlValidator urlVal = new UrlValidator(schemes, 0);
	      UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	     for (int sIndex = 0; sIndex < testQuery.length; sIndex++) {
	         ResultPair testPair = testQuery[sIndex];
	         boolean result = urlVal.isValidQuery(testPair.item);
	         System.out.print("\n\n values\n ");
	         System.out.println(testPair.item);
	         System.out.println(testPair.valid);
	         System.out.println(result);
	         
	      
	         
	         assertEquals(testPair.item, testPair.valid, result);
	         if (printStatus) {
	            if (result == testPair.valid) {
	               
	               System.out.println('.');
	               System.out.println(testPair.item);
	            } else {
	               System.out.println('X');
	            }
	         }
	      }
	      if (printStatus) {
	         System.out.println();
	      }

	   }
 
   //Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   //Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   //int[] testPartsIndex = {0, 0, 0, 0, 0};

 //---------------- Test data for individual url parts ----------------

   
   ResultPair[] testScheme = {new ResultPair("http", true),
           new ResultPair("ftp", true),
           new ResultPair("h3t://", false),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", false)};
 
ResultPair[] testAuthority = {new ResultPair("www.google.com", true),
        new ResultPair("go.com", true),
        new ResultPair("go.au", true),
        new ResultPair("0.0.0.0", true),
        new ResultPair("255.255.255.255", true),
        new ResultPair("256.256.256.256", false),
        new ResultPair("255.com", true),
        new ResultPair("1.2.3.4.5", false),
        new ResultPair("1.2.3.4.", false),
        new ResultPair("1.2.3", false),
        new ResultPair(".1.2.3.4", false),
        new ResultPair("go.a", false),
       new ResultPair("go.a1a", false),
        new ResultPair("go.1aa", false),
        new ResultPair("aaa.", false),
        new ResultPair(".aaa", false),
        new ResultPair("aaa", false),
        new ResultPair("", false)};

ResultPair[] testPort = {new ResultPair(":80", true),
        new ResultPair(":65535", true),
        new ResultPair(":0", true),
        new ResultPair("", true),
        new ResultPair(":-1", false),
       new ResultPair(":65636",false),
        new ResultPair(":65a", false)};

ResultPair[] testPath = {new ResultPair("/test1", true),
        new ResultPair("/t123", true),
        new ResultPair("/$23", true),
        new ResultPair("/..", false),
        new ResultPair("/../", false),
        new ResultPair("/test1/", true),
        new ResultPair("", true),
        new ResultPair("/test1/file", true),
        new ResultPair("/..//file", false),
        new ResultPair("/test1//file", false)};

ResultPair[] testQuery = {new ResultPair("?action=view", true),
        new ResultPair("?action=edit&mode=up", true), 
        new ResultPair("", true),
        new ResultPair("wrong_query", false),
        new ResultPair("wrong_query_1", false),
        new ResultPair("wrong_query_2", false)};

   
   
   
}
