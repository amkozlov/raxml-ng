#!groovy

pipeline {

  agent {
    label 'docker-host || docker-jenkins'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }  

  stages {
    stage('submodules') {
      agent {
        docker {
          reuseNode true
          image 'braintwister/ubuntu-20.04-clang-10:0.5'
        }
      }
      steps {
        sh 'git submodule update --init --recursive'
      }
    }
    stage('Build') {
      parallel {
        stage('clang-10') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-10'
              dir 'docker'
            }
          }
          steps {
            sh './build.sh clang-10 Release'
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: 'clang-10', pattern: 'build-clang-10/make.out')
            }
          }
        }
      }
    }
  }
  post {
    success {
      mail to: 'bernd.doser@h-its.org', subject: "SUCCESS: ${currentBuild.fullDisplayName}", body: "All fine."
    }
    failure {
      mail to: 'bernd.doser@h-its.org', subject: "FAILURE: ${currentBuild.fullDisplayName}", body: "Failed."
    }
  }
}
