#!groovy

pipeline {

  agent {
    label 'docker-host || docker-jenkins'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }

  parameters {
    string(name: 'BUILD_DIR_CLANG', defaultValue: 'build-clang-12')
    string(name: 'BUILD_DIR_GCC', defaultValue: 'build-gcc-11')
    string(name: 'BUILD_DIR_GCC_OPENMPI', defaultValue: 'build-gcc-11-openmpi')
  }

  stages {
    stage('Submodules') {
      agent {
        dockerfile {
          reuseNode true
          filename 'dockerfile-clang-12'
          dir 'docker'
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
        stage('clang-12') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-12'
              dir 'docker'
            }
          }
          steps {
            sh """
              rm -fr ${params.BUILD_DIR_CLANG} && mkdir -p ${params.BUILD_DIR_CLANG} && cd ${params.BUILD_DIR_CLANG}
              cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 |tee cmake.out
              make 2>&1 |tee make.out
            """
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: 'clang-12', pattern: "${params.BUILD_DIR_CLANG}/make.out")
            }
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh """
              rm -fr ${params.BUILD_DIR_GCC} && mkdir -p ${params.BUILD_DIR_GCC} && cd ${params.BUILD_DIR_GCC}
              cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 |tee cmake.out
              make 2>&1 |tee make.out
            """
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: 'gcc-11', pattern: "${params.BUILD_DIR_GCC}/make.out")
            }
          }
        }
        stage('gcc-11-openmpi') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh """
              rm -fr ${params.BUILD_DIR_GCC_OPENMPI} && mkdir -p ${params.BUILD_DIR_GCC_OPENMPI} && cd ${params.BUILD_DIR_GCC_OPENMPI}
              cmake -DCMAKE_BUILD_TYPE=Release -DUSE_MPI=ON .. 2>&1 |tee cmake.out
              make 2>&1 |tee make.out
            """
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: "${STAGE_NAME}", pattern: "${params.BUILD_DIR_GCC_OPENMPI}/make.out")
            }
          }
        }
      }
    }
    stage('Unit tests') {
      parallel {
        stage('clang-12') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-12'
              dir 'docker'
            }
          }
          steps {
            sh "cd ${params.BUILD_DIR_CLANG} && make test"
          }
          post {
            always {
              step([
                $class: 'XUnitPublisher',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: "${params.BUILD_DIR_CLANG}/test/*.xml"]]
              ])
            }
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh "cd ${params.BUILD_DIR_GCC} && make test"
          }
          post {
            always {
              step([
                $class: 'XUnitPublisher',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: "${params.BUILD_DIR_GCC}/test/*.xml"]]
              ])
            }
          }
        }
      }
    }
    stage('Regression tests') {
      parallel {
        stage('clang-12') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-12'
              dir 'docker'
            }
          }
          steps {
            sh "ngtest/runtest.py ${params.BUILD_DIR_CLANG}/bin/raxml-ng"
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh """
              ngtest/runtest.py ${params.BUILD_DIR_GCC}/bin/raxml-ng"
              docker/print_time.py
            """
          }
          post {
            always {
              plot csvFileName: 'plot-8d41db20-6490-4bce-8552-0698a4ef2ed6.csv',
                csvSeries: [[displayTableFlag: false, exclusionValues: '', file: 'test_timings.csv',
                inclusionFlag: 'OFF', url: '']], group: 'timings', numBuilds: '2', style: 'bar',
                title: 'Test timings', yaxis: 'Time/s'
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
