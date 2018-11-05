pipeline {
  agent any
  environment {
    CURRENT_BRANCH = "${BRANCH_NAME}"
  }
  stages {
    stage('Build') {
      steps {
        sh 'printenv'
        sh './build.sh'
      }
    }
	stage('Run Tests') {
	  steps {
        sh './test.sh'
      }
	}
	stage('Collect Code Coverage') {
	  steps {
	    withSonarQubeEnv('SonarQube') {
          sh './anal.sh'
        }
         step([$class: 'CoberturaPublisher', autoUpdateHealth: false, autoUpdateStability: false, coberturaReportFile: 'cov.xml', failUnhealthy: false, failUnstable: false, maxNumberOfBuilds: 0, onlyStable: false, sourceEncoding: 'ASCII', zoomCoverageChart: false])
         publishHTML (target: [
                allowMissing: false,
                keepAll: true,
                reportDir: 'bld/cov',
                reportFiles: 'index.html',
                reportName: "Code Coverage"
         ])
      }
	}
  }
}
