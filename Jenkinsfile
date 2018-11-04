pipeline {
  agent any
  stages {
    stage('Checkout') {
	  stages {
	    stage('Cleanup') {
          steps {
		    cleanWs()
		    checkout scm
          }
        }
	  }
	  post {
        failure {
          script {
            // CHANGE_ID is set only for pull requests, so it is safe to access the pullRequest global variable
            if (env.CHANGE_ID) {
              pullRequest.addLabel('Checkout Failed')
            }
          }
        }
	  }
	}
    stage('Build') {
      steps {
        echo 'TEST'
      }
    }
	stage('Run Tests') {
	  steps {
        echo 'TEST'
      }
	}
	stage('Collect Code Coverage') {
	  steps {
        echo 'TEST'
      }
	}
  }
}