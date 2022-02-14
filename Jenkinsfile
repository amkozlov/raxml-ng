#!groovy

pipeline {

  agent {
    label 'docker-host || docker-jenkins'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }  

  stages {
    stage('Submodules') {
      agent {
        docker {
          reuseNode true
          image 'braintwister/ubuntu-20.04-clang-10:0.5'
        }
      }
      steps {
        sh '''
          git submodule update --init --recursive
          git submodule add https://github.com/amkozlov/ngtest.git
        '''
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
    stage('Unit tests') {
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
            sh 'cd build-clang-10 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitPublisher',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-clang-10/test/*.xml']]
              ])
            }
          }
        }
      }
    }
    stage('Regression tests') {
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
            sh './ngtest/runtest.py ./bin/raxml-ng'
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
